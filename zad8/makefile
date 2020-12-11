all:
	cc baza.c main.c -o mydb -Wall --pedantic -ggdb
test: all
	./mydb baza.csv add_course qKJWFYIHQW "jEstem hardcorem" 202020ZIma
test-memory: all
	valgrind --leak-check=full ./mydb baza.csv add_course K0DT35T "Testowanie programow" 2020Z out.csv
test-stud: all
	./mydb baza.csv add_student Uczen Testowy 69420 mailJakikolwiek@gmail.com out.csv
test-przed: all
	./mydb baza.csv add_course K0DT35T "Testowanie programow" 2020Z out.csv
test-ocena: all
	./mydb baza.csv add_student_to_course K0DT35T 69420 3.5 "Jakis komentarz" out.csv
test-stud-oc: all
	./mydb baza.csv student_grades 123456
test-przed-oc: all
	./mydb baza.csv course_grades 1DA1245
test-stud-sort-normal: all
	./mydb baza.csv sort_students
test-stud-sort-back: all
	./mydb baza.csv sort_students_backwards
test-course-sort-name: all
	./mydb baza.csv sort_courses_by_name
test-course-sort-code: all
	./mydb baza.csv sort_courses_by_code