# pd2-sudoku

make
g++ -c Sudoku.cpp -o Sudoku.o
g++ -o give_question give_question.cpp Sudoku.o
g++ -o solve solve.cpp Sudoku.o

出題
./give_question

解題
./solve
