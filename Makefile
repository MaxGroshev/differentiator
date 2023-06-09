TARGET   = differ
MAKE_TEX = ./LaTeX/Makefile
CC       = gcc
CFLAGS   = -c -std=c++17

GR_DIR    = ./tree/graph_lib/
LOGS_DIR  = ./logs/
LATEX_DIR = ./LaTeX/
PY_GR_DIR = ./py_graph/
TREE_DIR  = ./tree/
PREF_OBJ  = ./obj/
PREF_STAT = ./logs/log_pics/


#Graphviz files
GR_LIB   = $(wildcard $(GR_DIR)*.cpp)
OBJ_LIB  = $(patsubst $(PREF_OBJ)%.cpp, %.o, $(GR_LIB))
#Tree files
TREE_SRC = $(wildcard $(TREE_DIR)*.cpp)
OBJ_TREE = $(patsubst $(PREF_OBJ)%.cpp, %.o, $(TREE_SRC))
#Common files
SRC      = $(wildcard *.cpp )                            #include of all files with .cpp
OBJ      = $(patsubst %.cpp, $(PREF_OBJ)%.o, $(SRC))     #turn .cpp into .o
#Logs files
LOGS_SRC = $(wildcard $(LOGS_DIR)*.cpp)
OBJ_LOGS = $(patsubst $(PREF_OBJ)%.cpp, %.o, $(LOGS_SRC))
#LaTeX files
LATEX_SRC = $(wildcard $(LATEX_DIR)*.cpp)
OBJ_LATEX = $(patsubst $(PREF_OBJ)%.cpp, %.o, $(LATEX_SRC))
#Py_graph files
PY_GR_SRC = $(wildcard $(PY_GR_DIR)*.cpp)
OBJ_PY_GR = $(patsubst $(PREF_OBJ)%.cpp, %.o, $(PY_GR_SRC))


all:     $(TARGET)

$(TARGET):  $(OBJ) $(OBJ_TREE) $(OBJ_LIB) $(OBJ_LOGS) $(OBJ_LATEX) $(OBJ_PY_GR)
	$(CC) -o $(TARGET) $(OBJ) $(OBJ_TREE) $(OBJ_LIB) $(OBJ_LOGS) $(OBJ_LATEX) $(OBJ_PY_GR)

$(PREF_OBJ)%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@


latex_t:
	pdflatex LaTeX/differ.tex pdf -o ./LaTeX/differ.pdf
	rm -rf  *.aux *.log

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(TARGET)

graphviz:
	dot $(GR_DIR)tree_dump.dot -T pdf -o $(PREF_STAT)tree_dump.pdf
	dot $(GR_DIR)tree_dump.dot -T png -o $(PREF_STAT)tree_dump.png

.PHONY : clean
clean:
	rm -rf $(PREF_OBJ)*.o $(TARGET) *.aux *.log vgcore.*
