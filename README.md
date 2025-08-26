# Task Manager

This is a basic Task Manager/Todo List program written in C++

The program contains functionality to add, edit, and remove tasks, as well as display all your tasks.
Tasks are all stored in a JSON file using the nlohmann JSON library.
UI text is colored using the fmt library.

There are two ways of using this program.
You can use the basic numbered user interface:

Choose one of the following...

1. Add Task
2. Remove Task
3. Edit Task
4. Sort Tasks
5. Show Tasks
6. Save and Exit

You can also use the advanced command-based interface. You can see a list of all commands by typing "todo help"

"todo clear" - clears the screen
"todo add (name)" - adds a task to the list
"todo remove (id)" - removes a task from the list
"todo edit (id) (characteristic) (new value)" - changes a value from a task
"todo sort (characteristic)" - sorts tasks by characteristic
"todo list" - lists all tasks
"todo exit" - exits the program
