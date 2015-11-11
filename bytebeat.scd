(
SynthDef("bytebeatFx", {
	arg amp = 0.2;
	var in, out;
	in = AudioIn.ar(2);
	//in = in.dup;
	//in = LeakDC.ar(MidEQ.ar(in * 0.5, 40, 1.0, 12));
	out = MidEQ.ar(LeakDC.ar(in), 2000, 1.0, 18);
	out = MidEQ.ar(LeakDC.ar(in), 80, 1.0, 18);
	//12.do({ out = AllpassN.ar(out, 0.05, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.01), 1.0) });
	out = GVerb.ar(out, 300, 3, drylevel:1.0, earlyreflevel:0.2, taillevel:0.2);
	out = CompanderD.ar(out) * amp;
	Out.ar(0, out);
}).store;
)

/*
(
play {
	var in, out;
	in = AudioIn.ar(2);
	//in = in.dup;
	//in = LeakDC.ar(MidEQ.ar(in * 0.5, 40, 1.0, 12));
	out = MidEQ.ar(LeakDC.ar(in), 40, 1.0, 12);
	//12.do({ out = AllpassN.ar(out, 0.05, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.01), 1.0) });
	out = GVerb.ar(out, 300, 10, drylevel:1.0, earlyreflevel:0.3, taillevel:0.1);
	out = CompanderD.ar(out);
	out;
}
)

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
*/