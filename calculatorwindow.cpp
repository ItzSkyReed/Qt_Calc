//Вариант 6: x^3, 10^x, 1/х

#include "calculatorwindow.h"
#include "./ui_calculatorwindow.h"
#include <QPushButton>
CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CalculatorWindow)
{
    ui->setupUi(this);

    // Подключаем сигналы кнопок к слоту onButtonClicked()
    // Указатель на кнопку; сигнал, который мы хотим подключить;
    // указатель на объект в котором находится кнопка; функция которая будет вызываться
    connect(ui->Button0, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button1, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button2, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button3, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button4, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button5, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button6, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button7, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button8, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);
    connect(ui->Button9, &QPushButton::clicked, this, &CalculatorWindow::onNumberButtonClicked);

    // Подключаем сигналы кнопок действий к слоту onActionButtonClicked()
    connect(ui->ButtonPlus, &QPushButton::clicked, this, &CalculatorWindow::onStandartActionClicked);
    connect(ui->ButtonMinus, &QPushButton::clicked, this, &CalculatorWindow::onStandartActionClicked);
    connect(ui->ButtonMultiply, &QPushButton::clicked, this, &CalculatorWindow::onStandartActionClicked);
    connect(ui->ButtonSubstract, &QPushButton::clicked, this, &CalculatorWindow::onStandartActionClicked);

    // Подключаем сигналы для кнопок, добавленных для задания
    connect(ui->Button10inNum, &QPushButton::clicked, this, &CalculatorWindow::on10inNumButtonClicked);
    connect(ui->ButtonInverse, &QPushButton::clicked, this, &CalculatorWindow::onInverseButtonClicked);
    connect(ui->ButtonToCube, &QPushButton::clicked, this, &CalculatorWindow::onToCubeButtonClicked);

    // Подключаем сигнал кнопки Clear к слоту onClearButtonClicked()
    connect(ui->ButtonClear, &QPushButton::clicked, this, &CalculatorWindow::onClearButtonClicked);

    // Подключаем сигнал кнопки равно к слоту onEqualButtonClicked()
    connect(ui->ButtonEquals, &QPushButton::clicked, this, &CalculatorWindow::onEqualButtonClicked);

    // Подключаем cигнал кнопки точка к слоту onDotButtonClicked()
    connect(ui->ButtonDot, &QPushButton::clicked, this, &CalculatorWindow::onDotButtonClicked);

    // Подключаем cигнал кнопки +/- к слоту onDotButtonClicked()
    connect(ui->ButtonPlusMinus, &QPushButton::clicked, this, &CalculatorWindow::onPlusMinusButtonClicked);

    // Подключаем cигнал кнопок MR/MS/M+/M-/MC к слоту onDotButtonClicked()
    connect(ui->ButtonMR, &QPushButton::clicked, this, &CalculatorWindow::onMRButtonClicked);
    connect(ui->ButtonMS, &QPushButton::clicked, this, &CalculatorWindow::onMSButtonClicked);
    connect(ui->ButtonMMinus, &QPushButton::clicked, this, &CalculatorWindow::onMMinusButtonClicked);
    connect(ui->ButtonMPlus, &QPushButton::clicked, this, &CalculatorWindow::onMPlusButtonClicked);
    connect(ui->ButtonMClear, &QPushButton::clicked, this, &CalculatorWindow::onMClearButtonClicked);


    is_action_selected = false; // Флаг, который указывает, что действие уже выбрано. Он используется для очистки экрана при вводе нового числа после выбора действия
    is_dot_pressed = false; // Флаг, который указывает, что точка стоит.
    accumulator = 0; // Переменная, которая используется для хранения промежуточного результата. Она содержит значение, которое было введено до выбора действия.
    current_action = '\0'; //переменная, которая используется для хранения текущего действия. Она содержит символ, соответствующий нажатой кнопке действия (+ или -)
    saved_num = nullptr; // Хранимое для MS число
    ui->ResultDisplay->setText("0"); // Устанавливаем стандартное значение на 0
}

CalculatorWindow::~CalculatorWindow()
{
    delete ui;
}


void CalculatorWindow::onNumberButtonClicked()
{
    // Определяем, какая кнопка цифры была нажата
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    // Получаем текст нажатой кнопки
    QString buttonText = clickedButton->text();

    // Если действие уже выбрано, то очищаем экран и сбрасываем флаг is_action_selected
    if (is_action_selected) {
        ui->ResultDisplay->setText("0");
        is_action_selected = false;
    }

    // Получаем текущее значение на дисплее
    QString currentValue = ui->ResultDisplay->text();

    if (is_dot_pressed) { // Обновляем значение на дисплее, добавляя к нему нажатую цифру, если точка нажата
        ui->ResultDisplay->setText(currentValue + buttonText);
    }
    else {
        // Обновляем значение на дисплее, добавляя к нему нажатую цифру, если точка не нажата
        double newValue = currentValue.toDouble() * 10 + buttonText.toDouble();
        ui->ResultDisplay->setText(QString::number(newValue));
    }
}


void CalculatorWindow::onStandartActionClicked()
{
    // Определяем, какая кнопка действия была нажата
    // Для этого используем функцию qobject_cast, которая преобразует указатель на объект QObject
    // (в данном случае, объект-источник сигнала) в указатель на объект производного класса QPushButton
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    // Получаем текст нажатой кнопки и преобразуем его в символ (char)
    // Затем преобразуем QString в QByteArray с помощью метода toLatin1()
    // Затем получаем первый символ из QByteArray с помощью метода at(0)
    char buttonText = *clickedButton->text().toLatin1();

    // Сохраняем текущее значение экрана в переменной accumulator
    accumulator = ui->ResultDisplay->text().toDouble();

    // Сохраняем текущее действие в переменной current_action
    current_action = buttonText;

    // Устанавливаем флаг is_action_selected в true, чтобы показать, что действие выбрано
    is_action_selected = true;
    is_dot_pressed = false;
}

// Функция вызывается при нажатии на кнопку "x^3"
void CalculatorWindow::onToCubeButtonClicked()
{
    double current_value = ui->ResultDisplay->text().toDouble();
    double result = pow(current_value, 3);
    ui->ResultDisplay->setText(QString::number(result));
    is_dot_pressed = false;
}

// Функция вызывается при нажатии на кнопку "10^x"
void CalculatorWindow::on10inNumButtonClicked()
{
    double current_value = ui->ResultDisplay->text().toDouble();
    double result = pow(10, current_value);
    ui->ResultDisplay->setText(QString::number(result));
    is_dot_pressed = false;
}

// Функция вызывается при нажатии на кнопку "1/x"
void CalculatorWindow::onInverseButtonClicked()
{
    double current_value = ui->ResultDisplay->text().toDouble();
    if (current_value == 0) {
        // Обработка ошибки деления на ноль
        ui->ResultDisplay->setText("Error");
        return;
    }
    double result = 1 / current_value;
    ui->ResultDisplay->setText(QString::number(result));
    is_dot_pressed = false;
}

// Функция вызывается при нажатии на кнопку "=", выводит результат в дисплей.
void CalculatorWindow::onEqualButtonClicked()
{
    double current_value = ui->ResultDisplay->text().toDouble();
    double result;
    switch (current_action) {
    case '+':
        result = accumulator + current_value;
        break;
    case '-':
        result = accumulator - current_value;
        break;
    case '*':
        result = accumulator * current_value;
        break;
    case '/':
        if (current_value == 0) { // Обработка ошибки деления на ноль
            ui->ResultDisplay->setText("Error");
            return;
        }
        result = accumulator / current_value;
        break;
    default:
        return; // Если вдруг символ неопознан, просто завершаем функцию
    }
    ui->ResultDisplay->setText(QString::number(result));
    is_dot_pressed = false;
}

// Добавление точки к текущему числу
void CalculatorWindow::onDotButtonClicked()
{
    QString currentText = ui->ResultDisplay->text();

    // Проверяем, содержит ли текущий текст уже точку, чтобы избежать повторного добавления
    if (!is_dot_pressed) {
        currentText.append("."); // Добавляем точку к числу
        is_dot_pressed = true; // Активируем флаг
        ui->ResultDisplay->setText(currentText);
    }
}

// Функция для очистки дисплея, всех временных переменных
void CalculatorWindow::onClearButtonClicked()
{
    ui->ResultDisplay->setText("0");
    is_action_selected = false;
    is_dot_pressed = false;
    accumulator = 0;
    current_action = '\0';
}

// Функция добавляющая/убирающая минус у числа
void CalculatorWindow::onPlusMinusButtonClicked() {
    QString currentText = ui->ResultDisplay->text();
    ui->ResultDisplay->setText(QString::number(currentText.toDouble() * -1)); // Умножаем на -1
}

// Функция для сохранения числа актуального на экране числа в памяти
void CalculatorWindow::onMSButtonClicked() {
    saved_num = ui->ResultDisplay->text();
}

// Функция для очищения числа актуального на экране числа в памяти
void CalculatorWindow::onMClearButtonClicked() {
    saved_num = nullptr;
}

// Функция для прибавления актуального на экране числа к числу в памяти
void CalculatorWindow::onMPlusButtonClicked() {
    saved_num = QString::number(saved_num.toDouble() + ui->ResultDisplay->text().toDouble());
}

// Функция для вычитания актуального на экране числа к числу в памяти
void CalculatorWindow::onMMinusButtonClicked() {
    saved_num = QString::number(saved_num.toDouble() - ui->ResultDisplay->text().toDouble());
}


// Функция для отображения сохраненного числа
void CalculatorWindow::onMRButtonClicked() {
    // Проверяем, если сохраненное число не равно нулевому указателю, тогда выводим его на экран
    if (saved_num != nullptr) {
            ui->ResultDisplay->setText(saved_num);
        }
    if (saved_num.contains('.')) {
            is_dot_pressed = true;
        }
}
