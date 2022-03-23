The Alpha-Beta-Zero to dq0 block performs a transformation of αβ0 Clarke components in a fixed reference frame to dq0 Park components in a rotating reference frame.

The dq0 to Alpha-Beta-Zero block performs a transformation of dq0 Park components in a rotating reference frame to αβ0 Clarke components in a fixed reference frame.



The block supports the two conventions used in the literature for Park transformation:

Rotating frame aligned with A axis at t = 0. This type of Park transformation is also known as the cosine-based Park transformation.

Rotating frame aligned 90 degrees behind A axis. This type of Park transformation is also known as the sine-based Park transformation. Use it in Simscape™ Electrical™ Specialized Power Systems models of three-phase synchronous and asynchronous machines.

Knowing that the position of the rotating frame is given by ω.t (where ω represents the frame rotation speed), the αβ0 to dq0 transformation performs a −(ω.t) rotation on the space vector Us = uα + j· uβ. The homopolar or zero-sequence component remains unchanged.

Depending on the frame alignment at t = 0, the dq0 components are deduced from αβ0 components as follows:

When the rotating frame is aligned with A axis, the following relations are obtained:

The inverse transformation is given by
