clc; clear all;

path = "fir.wav";
[samples, fs] = audioread(path);

b = 1;
a = [1, 0.2];

x = zeros(length(samples), 1);
x(1) = 1;
assert (length(x) == length(samples))

y = filter(b,a,x);

idx = 1
prec = 1e-6;
for i = y
  assert ( (abs(i(idx) - samples(idx)) < prec ), "Should be %f, but is %f\n", i, samples(idx));
  idx += 1;
 end

 fprintf("FIR is correct\n");
