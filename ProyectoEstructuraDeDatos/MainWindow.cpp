#include "MainWindow.h"
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include "List.h"
#include "Queue.h"
#include "Stack.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
enum ESTRUCTURA
{
    QUEUE, 
    LISTA, 
    STACK
};

List* lista;
Queue* queue;
Stack* stack = new Stack();
int estructura = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //ui.rb_listaEnlazada->setChecked(true);
    hideMenu();
}

MainWindow::~MainWindow()
{}

void MainWindow::on_rb_listaEnlazada_clicked() {
    estructura = LISTA;
    //ui.label_titulo->setText("Listas Enlazadas");
    ui.butt_toolbar->setText("Toolbar of List");
    ui.frame_opciones->hide();
    hideMenu();
}

void MainWindow::on_rb_queue_clicked() {
    estructura = QUEUE;
    //ui.label_titulo->setText("Queue");
    ui.butt_toolbar->setText("Toolbar of Queue");
    ui.frame_opciones->hide();
    hideMenu();
}

void MainWindow::on_rb_stack_clicked() {
    estructura = STACK;
    //ui.label_titulo->setText("Stack");
    ui.butt_toolbar->setText("Toolbar of Stack");
    ui.frame_opciones->hide();
    hideMenu();
}

void MainWindow::on_butt_toolbar_clicked() {
    switch (estructura) {
    case LISTA:
        ui.butt_toolbar->setText("Lista");
        ui.frame_opciones->show();
        break;
    case QUEUE:
        ui.butt_toolbar->setText("Queue");
        ui.frame_opciones->show();
        break;
    case STACK: 
        ui.butt_toolbar->setText("Stack");
        ui.frame_opciones->show();
        break;
    }
}

void MainWindow::on_butt_crear_lista_clicked() {
    switch (estructura) {
    case LISTA:
        lista = new List();
        ui.butt_toolbar->setText("Toolbar");
        refreshList();
        showMenu();
        break;
    case QUEUE:
        queue = new Queue();
        ui.butt_toolbar->setText("Toolbar");
        refreshList();
        showMenu();
        break;
    case STACK:
        stack = new Stack();
        queue = new Queue();
        ui.butt_toolbar->setText("Toolbar");
        refreshList();
        showMenu();
    }
}

void MainWindow::on_butt_editar_lista_clicked() {
    ui.butt_toolbar->setText("Toolbar");
}

void MainWindow::on_butt_guardar_lista_clicked() {
    bool ok;
    ui.butt_toolbar->setText("Toolbar");
    hideMenu();
    QString nameInput = QInputDialog::getText(this, tr("Listas Enlazadas"), tr("Nombre de archivo:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    string fileName = nameInput.toStdString() + ".csv";
    if (!nameInput.isEmpty()) {
        ofstream File (fileName);
        while (File.is_open()) {
            for (int i = 0; i < lista->size(); i++) {
                File << lista->valueAt(i) << "\n";
            }
            File.close();
        }
        QMessageBox::information(this, tr("Listas Enlazadas Successfuly"), tr("Archivo creado exitosamente!"));
    }    
}

void MainWindow::on_butt_agregar_clicked() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    string input = ui.txt_insertar->text().toStdString();
    cin >> input;
    stringstream s(input);
    int num_input;
    if ((s >> num_input).fail() || !(s >> std::ws).eof()) {
        QMessageBox::warning(this, tr("Listas Enlazadas"), tr("Ingrese un Dato!"));
    }
    else {
        switch (estructura) {
        case LISTA:
            num_input = stoi(input);
            lista->insertNode(num_input);
            break;
        case QUEUE:
            num_input = stoi(input);
            queue->enqueue(num_input);
            break;
        case STACK:
            num_input = stoi(input);
            stack->push(num_input);
            break;
        }
    }
    refreshList();
    ui.txt_insertar->clear();
}

void MainWindow::on_butt_buscar_clicked() {
    string str_valor = ui.txt_buscar->text().toStdString();
    cin >> str_valor;
    stringstream s(str_valor);
    int valor;
    if ((s >> valor).fail() || !(s >> std::ws).eof()) {
        QMessageBox::warning(this, tr("Listas Enlazadas"), tr("Ingrese un Dato!"));
    }
    else {
        valor = stoi(str_valor);
        switch (estructura) {
        case LISTA:
            if (lista->size() == 0)
                QMessageBox::warning(this, tr("Buscar"), tr("Lista Vacia!!"));
            else {
                bool exists = lista->contains(valor);
                if (exists)
                    QMessageBox::information(this, tr("Buscar"), tr("Se encontro el valor correctamente!"));
                else
                    QMessageBox::warning(this, tr("Buscar"), tr("No se pudo encontrar el valor ingresado!"));
            }
            break;
        case QUEUE:
            if (queue->getSize() == 0) {
                QMessageBox::warning(this, tr("Buscar"), tr("Lista Vacia!!"));
            }
            else {
                bool exists = queue->contains(valor);
                if (exists)
                    QMessageBox::information(this, tr("Buscar"), tr("Se encontro el valor correctamente!"));
                else
                    QMessageBox::warning(this, tr("Buscar"), tr("No se pudo encontrar el valor ingresado!"));
            }
            break;
        }        
    }
    ui.txt_buscar->clear();
}

void MainWindow::on_butt_eliminar_clicked() {
    switch (estructura) {
    case LISTA:
        if (ui.combo_eliminar->count() == 0) {
            QMessageBox::warning(this, tr("Eliminar"), tr("Lista Vacia!"));
        }
        else {
            int value = stoi(ui.combo_eliminar->currentText().toStdString());
            bool exists = lista->deleteNode(value);
            if (exists) {
                refreshList();
                QMessageBox::information(this, tr("Eliminar"), tr("Se elimino correctamente!"));
            }
            else
                QMessageBox::warning(this, tr("Eliminar"), tr("No se pudo encontrar el elemento seleccionado!"));
        }
        break;
    case QUEUE:
        if (queue->getSize() == 0) {
            QMessageBox::warning(this, tr("Dequeue"), tr("Lista Vacia!"));
        }
        else {
            int valor = queue->dequeue();
            refreshList();
            QMessageBox::information(this, tr("Dequeue"), tr("Dequeue"));            
        }
        break;
    case STACK:
        if (stack->getSize() == 0) {
            QMessageBox::warning(this, tr("Pop"), tr("Lista Vacia!"));
        }
        else {
            int valor = stack->pop();
            refreshList();
            QMessageBox::information(this, tr("Pop"), tr("Pop"));
        }
        break;
    }
    
}


void MainWindow::hideMenu() {
    ui.frame_opciones->hide();
    ui.label_insertar->hide();
    ui.label_eliminar->hide();
    ui.txt_insertar->hide();
    ui.combo_eliminar->hide();
    ui.label_buscar->hide();
    ui.butt_buscar->hide();
    ui.txt_buscar->hide();
    ui.butt_agregar->hide();
    ui.butt_eliminar->hide();
}

void MainWindow::showMenu() {
    ui.frame_opciones->hide();
    ui.label_buscar->show();
    ui.txt_buscar->show();
    ui.butt_buscar->show();
    switch (estructura) {
    case LISTA:
        ui.label_insertar->setText("Insertar");
        ui.label_insertar->show();
        ui.txt_insertar->show();
        ui.butt_agregar->setText("Insertar");
        ui.butt_agregar->show();

        ui.label_eliminar->setText("Eliminar");
        ui.label_eliminar->show();
        ui.combo_eliminar->show();
        ui.butt_eliminar->setText("Eliminar");
        ui.butt_eliminar->show();
        break;
    case QUEUE:
        ui.label_insertar->setText("Enqueue");
        ui.label_insertar->show();
        ui.txt_insertar->show();
        ui.butt_agregar->setText("Enqueue");
        ui.butt_agregar->show();

        ui.butt_eliminar->setText("Dequeue");
        ui.butt_eliminar->show();
        break;
    case STACK:
        ui.label_insertar->setText("Push");
        ui.label_insertar->show();
        ui.txt_insertar->show();
        ui.butt_agregar->setText("Push");
        ui.butt_agregar->show();

        ui.butt_eliminar->setText("Pop");
        ui.butt_eliminar->show();
        break;
    }
}

void MainWindow::refreshList() {
    QPixmap pixmap("pointer.png");
    ui.combo_eliminar->clear();    
    this->clearGraphView(ui.layout);
    switch (estructura)
    {
    case LISTA:
        for (int i = 0; i < lista->size(); i++) {
            ui.combo_eliminar->addItem(QString::number(lista->valueAt(i)));
        }
        for (int i = 0; i < lista->size(); i++) {
            QLabel* pointer = new QLabel();
            pointer->setPixmap(pixmap.scaled(20, 20));
            pointer->setAlignment(Qt::AlignCenter);

            QLabel* label = new QLabel(QString::number(lista->valueAt(i)));
            label->setAlignment(Qt::AlignCenter);
            if (i == 0)
                label->setStyleSheet("QLabel { background-color : blue; color : white; border-radius: 5px; min-height : 40px; max-height : 40px; font-size : 15px;}");
            else
                label->setStyleSheet("QLabel { background-color : gray; color : white; border-radius: 5px; min-height : 40px; max-height : 40px; font-size : 15px;}");
            ui.layout->addWidget(label);
            ui.layout->addWidget(pointer);
        }
        break;
    case QUEUE:
        for (int i = 0; i < queue->getSize(); i++) {
            QLabel* pointer = new QLabel();
            pointer->setPixmap(pixmap.scaled(20, 20));
            pointer->setAlignment(Qt::AlignCenter);
            QLabel* label = new QLabel(QString::number(queue->print(i)));
            label->setAlignment(Qt::AlignCenter);
            if (i == queue->getSize() - 1) 
                label->setStyleSheet("QLabel { background-color : blue; color: white; border-radius: 5px; min-height : 40px; max-height : 40px; font-size : 15px;}");
            else
                label->setStyleSheet("QLabel { background-color : gray; color : white; border-radius: 5px; min-height : 40px; max-height : 40px; font-size : 15px;}");
            ui.layout->insertWidget(0, pointer);
            ui.layout->insertWidget(0, label);
        }
        break;
    case STACK:
        for (int i = 0; i < stack->getSize(); i++) {

            QLabel* pointer = new QLabel();
            pointer->setPixmap(pixmap.scaled(20, 20));
            pointer->setAlignment(Qt::AlignCenter);

            QLabel* label = new QLabel(QString::number(stack->print(i)));
            label->setAlignment(Qt::AlignCenter);
            if (i == stack->getSize() - 1)
                label->setStyleSheet("QLabel { background-color : blue; color : white; min-height : 40px; max-height : 40px; font-size : 15px;}");
            else
                label->setStyleSheet("QLabel { background-color : gray; color : white; min-height : 40px; max-height : 40px; font-size : 15px;}");
            ui.layout->insertWidget(0, pointer);
            ui.layout->insertWidget(0, label);
        }
        break;
    }
    QLabel* null_node = new QLabel("NULLPTR");
    null_node->setAlignment(Qt::AlignCenter);
    null_node->setStyleSheet("QLabel { background-color : red; color : white; min-height : 40px; max-height : 40px; font-size : 15px;}");
    ui.layout->addWidget(null_node);
    ui.scroll_content->setLayout(ui.layout);
}

void MainWindow::clearGraphView(QLayout* layout) {
    if (layout == NULL)
        return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearGraphView(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}