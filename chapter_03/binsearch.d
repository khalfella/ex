
pid$target::binsearch*:entry
{
	self->ts = timestamp;
}

pid$target::binsearch*:return
{
	@t[probefunc] = lquantize(timestamp - self->ts,0,3000,100);
	self->ts = 0;
}
