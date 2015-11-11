(
play {
	var t, f, out;
	t = PulseCount.ar(Impulse.ar([8000, 8100]));

	f =	(t >> 3) | (t >> 15) & (t * 15);

	f = f % 256;
	//f = (f - 3 % 256) / 127-1 * 3;
	out = HPF.ar(f, 20).tanh;
	out = LeakDC.ar(out);
	out = CompanderD.ar(out);
	out = GVerb.ar(out);
}
)

(
{
	var t = PulseCount.ar(Impulse.ar(8e3));
	a = (t * 15);
	b = (t >> 3);
	c = a & b;
	c % 256;
}.play
)


(
play {
	var in, out;
	in = AudioIn.ar(2);
	in = MidEQ.ar(in, 40, 0.7, 24);
	out = in;
	out = LeakDC.ar(out);
	32.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 4.0) });
	out = GVerb.ar(out);
	out = CompanderD.ar((in * 1.0) + (out * 0.5));
}
)
