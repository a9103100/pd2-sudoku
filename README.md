# pd2-sudoku

make
g++ -c Sudoku.cpp -o Sudoku.o
g++ -o give_question give_question.cpp Sudoku.o
g++ -o solve solve.cpp Sudoku.o

出題
./give_question

解題
./solve

想法
先把空格的行、列、方格有的數字可能性刪除
將只剩一個可能性的空格填入
填滿了檢查數獨是否有錯
有錯則無解，正確則唯一解
若剩餘的空格可能性超過一個以上
進入函式使用至青法
若為多組解印出2
