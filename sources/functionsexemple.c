
/*
	afc bp, 0
	afc sp, 0
	call main
	stop
get:
	push bp
	cop bp, sp
	add sp, sp, 2
	cop [bp+1], [bp+-3]
	pri [bp+1]
	cop [bp+1], [bp+-4]
	pri [bp+1]
get_end:
	leave
	ret
main:
	push bp
	cop bp, sp
	add sp, sp, 3
	afc [bp+1], 1 
	afc [bp+2], 2 
	push [bp+2]
	push [bp+1]
	call get
main_end:
	leave
	ret
*/

int get(int v, int c)
{
	printf(v);
	printf(c);
}

int main()
{
	get(1, 2);
}
