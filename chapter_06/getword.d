#!/usr/sbin/dtrace -s

pid$target::getword:entry {
	self->arg0 = arg0;
}

pid$target::getword:return
/self->arg0/
{
	printf("getword returns -> \"%s\" \n", copyinstr(self->arg0));
	self->arg0 = 0;
}
