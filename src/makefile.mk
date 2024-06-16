ssg: headers.h main.o generate_site.o generate_html.o
	gcc main.o generate_site.o generate_html.o -o ssg
main.o: headers.h main.c
	gcc main.c -c -o main.o
generate_site.o: headers.h generate_site.c
	gcc generate_site.c -c -o generate_site.o
generate_html.o: headers.h generate_html.c
	gcc generate_html.c -c -o generate_html.o