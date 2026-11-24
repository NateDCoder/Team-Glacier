# TA feedback, items 7, 8, 9 (Team Glaciers)

Diagram for these changes: `Project2_items7-9.vpp` (copy of `project2updated.vpp`, branch `ta-feedback-items-7-9`).
Nothing here is merged into main. Items 1 to 6 are being handled separately.

## 7. How is rotation stored, and how does it interact with Polygon?

**Rotation is stored in exactly one place: the `Polygon` (`mRotation`, in turns).** Nothing else keeps a copy.

- `Component` **has** a `Polygon` (composition, role `polygon`). It no longer inherits from Polygon.
- `Component::SetRotation(rotation)` is virtual. The default body is `polygon.SetRotation(rotation)`.
- `Component::Draw(graphics)` calls `polygon.DrawPolygon(graphics, position.x, position.y)`. The polygon rotates about its own origin, so the position stays in Component and is passed in at draw time.
- Removed duplicates: `Component.rotation`, `Motor.rotation`, `Pulley.sinkRotation`, `Pulley.sourceRotation`, and the matching setters (`SetSinkRotation`, `SetSourceRotationRotation`).
- `RotationSource` stores no rotation. It only keeps its list of sinks and forwards `SetRotation(r)` to each one.
- `RotationSink` stores no rotation. It keeps the `Component` it belongs to and calls `component.SetRotation(r)`.
- `Pulley::SetRotation(r)` overrides the Component version. It calls the base (turns its polygon), then `source.SetRotation(r)`, then drives its belt follower with `r * radius / followerRadius`.
- `SnowBlower::SetRotation(r)` overrides it too. It does not turn its polygon; it stores the rate that sets the snow output.

## 8. Components that need more than one polygon

- `Component` owns one `Polygon`, the part that receives `SetRotation`.
- Only `Motor` needs a second one. A motor has a static body and a rotating shaft.
  - The shaft is the Component polygon, so it spins when the motor sets its own rotation.
  - The body is a second `Polygon` that `Motor` owns (composition, role `body`). It never rotates.
  - `Motor::Draw(graphics)` draws `body` first and then calls `Component::Draw` for the shaft, so the shaft sits in front of the body.
- Pulley, Shape and SnowBlower each use just the one inherited polygon.
- If a future component needs three or more polygons, `Component.polygon` can become a `vector<Polygon>`. The change would stay inside Component.

## 9. What happens when SetMachineFrame() and SetMachineNumber() are called?

Both live on `MachineSystem`. `MachineSystem` holds one `Machine` (multiplicity 1, never both machines in memory), the frame rate, the current frame and the current time. Frames become seconds only in `SetMachineFrame`. Nothing below `MachineSystem` sees a frame number.

### SetMachineFrame(frame)
1. If `frame < currentFrame`, we are going backwards. Call `machine.Reset()` and set `currentFrame = 0`, `time = 0`. `Machine::Reset` calls `Reset()` on each component (motor rotation to 0, snow cleared).
2. Step forward one frame at a time while `currentFrame < frame`:
   - `currentFrame++`
   - `time = currentFrame / frameRate`
   - `machine.SetTime(time)`

   Stepping one frame at a time keeps the snow physics the same however far we jump.
3. `Machine::SetTime(time)` calls `SetTime(time)` on every component in its vector.
4. `Motor::SetTime(time)`: `rotation = time * speed`. It turns its own shaft polygon and calls `source.SetRotation(rotation)`.
5. `RotationSource::SetRotation(rotation)` calls `sink.SetRotation(rotation)` for each connected sink.
6. `RotationSink::SetRotation` calls `component.SetRotation(rotation)`.
   - Shape (flag): `Component::SetRotation` turns the polygon.
   - Pulley: turns its polygon, forwards to its own source, and drives the belted pulley at the speed ratio.
   - SnowBlower: stores the rate for snow output.
7. `SnowBlower::SetTime(time)` works out the time since its last update, spawns particles at the stored rate, and updates each `Snowflake` (gravity 15 px/s squared).
8. `GetMachineTime()` returns `time`.

### SetMachineNumber(n)
1. `MachineSystem` picks the matching factory (`ChooseFactory(n)`) and creates it as a local object. The factory is never stored.
2. The factory builds a new `Machine` and returns it, with the components added in draw order. Posts go in before the belts and pulleys that sit in front of them.
3. `MachineSystem` assigns it to its `machine` pointer. The old machine's last reference goes away here, so only one machine exists at a time.
4. The frame and time reset to 0, so the new machine starts clean.
5. `GetMachineNumber()` then returns `n`, kept in one place only.

## UML changes made in `Project2_items7-9.vpp`

See the checklist at the bottom of this file once the edit is finished.
