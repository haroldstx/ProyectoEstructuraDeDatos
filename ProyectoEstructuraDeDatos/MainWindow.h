#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void hideMenu();
    void showMenu();
    void refreshList();
    void clearGraphView(QLayout*);

private slots:
    void on_butt_toolbar_clicked();
    void on_butt_crear_lista_clicked();
    void on_butt_editar_lista_clicked();
    void on_butt_guardar_lista_clicked();
    void on_butt_agregar_clicked();
    void on_butt_buscar_clicked();
    void on_butt_eliminar_clicked();
    void on_rb_listaEnlazada_clicked();
    void on_rb_queue_clicked();
    void on_rb_stack_clicked();
    
private:
    Ui::MainWindowClass ui;
};

class Node
{
public:
    Node* next;
    int value;
    Node(int value);
    ~Node();
};

class Stack
{
private:
    Node* head;
    Node* tail;
    int size;
    void incrementSize();
    void decrementSize();
public:
    Stack();
    ~Stack();
    void push(int);
    int pop();
    int getSize();
    int print(int);
    bool contains(int);
};

Stack::Stack() {
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}


class Queue
{
private:
    Node* tail;
    Node* head;
    int size;
    void incrementSize();
    void decrementSize();
public:
    Queue();
    void enqueue(int);
    int dequeue();
    int getSize();
    int print(int);
    bool contains(int);
};

Queue::Queue() {
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}


class List
{
private:
    Node* first;
public:
    List();
    ~List();
    void insertNode(int);
    void printList();
    int size();
    int valueAt(int index);
    bool contains(int valor);
    bool deleteNode(int valueToDelete);
};
