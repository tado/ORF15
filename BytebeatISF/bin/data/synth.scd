(
SynthDef("bytebeatFx", {
	arg amp = 0.2;
	var in, eq1, eq2, out;
	in = AudioIn.ar(2);

	eq1 = MidEQ.ar(LeakDC.ar(in), 8000, 1.4, 8);
	eq2 = MidEQ.ar(LeakDC.ar(in), 40, 1.4, 8);
	out = (eq1 + eq2) * 0.5;
	out = GVerb.ar(out, 300, 3, drylevel:1.0, earlyreflevel:0.2, taillevel:0.2);
	out = CompanderD.ar(out);

	Out.ar(0, out * amp);
}).store;

SynthDef("col_closesaw", {
	arg fadeTime = 10, n = 0, rq = 0.3, detune = 0.001, base = 22, ratio = 1.5, harm = 1.5, amp = 0.1, gate=0;
	var lfo, env, out;
	env = EnvGen.kr(Env.new([0,1], [fadeTime], 'sine'));
	lfo = SinOsc.ar(rrand(0.03, 0.05), 0, 100, 600);
	out = Saw.ar([base+detune.rand, base+detune.rand] * (ratio ** n)) * amp
	+ Saw.ar([base*harm+detune.rand, base*harm+detune.rand] * (ratio ** n)) * amp;
	out = out * env;
	out = RLPF.ar(out, lfo * (1.5 ** n), rq).clip2 * 0.5;
	out = out * EnvGen.kr(Env.adsr(releaseTime:10), gate, doneAction: 2);
	Out.ar(3, out);
}).store;

SynthDef("col_closefx", {
	arg lpf=440, rq=0.5, amp=0.5;
	var in, out;
	in = In.ar(3, 2);
	32.do({ in = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 2.0) });
	out = MidEQ.ar(in, 50, 1.0, 12) * amp;
	Out.ar(0, out);
}).store;
)


Synth("col_closefx");
Synth("col_closesaw",[n:0, gate:1]);
