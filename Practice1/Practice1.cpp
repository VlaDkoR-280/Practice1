#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;


struct Date {
    short day;
    short month;
    short year;
};

struct Transport {
    char* type;
    char* number;
    float lenght;
    short time;
    Date date;
};
template <typename Data>
class MyList {
public:

    struct Node {
        Node* next;
        Data* data;
    }*node;

    MyList() {
        node = new Node;
        node->next = NULL;
        node->data = NULL;
    }

    MyList(Data** data, int size) {
        if (size == 0) return;
        node = new Node;
        node->data = *data;
        Node* next = node;
        for (int i = 1; i < size; i++) {
            next = next->next = new Node;
            next->data = data[i];
        }
        next->next = node;
        _size += size;
    }

    ~MyList() {
        Node* next = node->next;
        free(node);
        for (int i = 1; i < _size; i++) {
            Node* buf = next->next;
            delete next;
            next = buf;
        }
    }

    Data GetDataAndToNext() {
        Data data = *node->data;
        node = node->next;
        return data;
    }

    Data ToNext() {
        node = node->next;
        return *node->data;
    }

    Data getData() {
        return *node->data;
    }

    Data* getAdressData() {
        return node->data;
    }

    Data getNextData() {
        return *node->next->data;
    }

    void DeleteItem() {
        if (_size == 0) return;
        if (_size == 1) {
            free(node);
            node = NULL;
        }
        else if (_size > 1) {
            Node* prev = GetPrevElement();
            prev->next = node->next;
            free(node);
            node = prev->next;
        }

        _size--;

    }

    void DeleteNextItem() {
        Node* next = node->next;
        node->next = next->next;
        free(next);
        _size--;
    }

    void AddElementToNext(Data* data) {
        if (_size == 0) {
            node = new Node;
            node->next = node;
            node->data = data;
        }
        else {
            Node* prevNext = node->next;
            node->next = new Node;
            node->next->next = prevNext;
            node->next->data = data;
        }
        _size++;
    }


    int getSize() { return _size; }

private:
    int _size = 0;

    Node* GetPrevElement() {
        Node* next = node;
        for (int i = 1; i < _size; i++) {
            next = next->next;
        }
        return next;
    }
};

class TableCreater {
public:

    enum TextPosition {
        Start, Centre, End
    };

    int width;
    int sizeLines;

    struct LineData {
        int* sizeItems;
        struct ItemData {
            char* data;
            int widthItem;
            TextPosition pos;
        }*items;
    }**lines;

    /// <summary>
    /// Создание таблицы
    /// </summary>
    /// <param name="width">ширина таблицы</param>
    /// <param name="sizeLines">Количество строк в таблице</param>
    TableCreater(int width, int sizeLines) {
        this->width = width; this->sizeLines = sizeLines;
        lines = (TableCreater::LineData**)calloc(this->sizeLines, sizeof(TableCreater::LineData*));
    }

    ~TableCreater() {
        ClearData();
    }

    /// <summary>
    /// Очистка lines
    /// </summary>
    void ClearData() {
        if (lines == NULL) return;
        for (int i = 0; i < sizeLines; i++) {
            for (int j = 0; j < *lines[i]->sizeItems; j++) {
                delete lines[i]->items[j].data;
            }
            free(lines[i]->items);
            delete (lines[i]->sizeItems);
            free(lines[i]);

        }
        free(lines);
        return;
    }

    void CreateTable(int sizeLines, int width) {
        this->sizeLines = sizeLines;
        this->width = width;
        lines = (TableCreater::LineData**)calloc(this->sizeLines, sizeof(TableCreater::LineData*));
    }
    /// <summary>
    /// Изменение данных строки
    /// </summary>
    /// <param name="indexLine">индекс строки</param>
    /// <param name="lineData">Данные строки</param>
    void setElementsToLine(int indexLine, LineData* lineData) {
        if (indexLine + 1 > sizeLines) {
            cout << "Error size"; return;
        }
        lines[indexLine] = lineData;
    }

    /// <summary>
    /// Получение данных ячейки
    /// </summary>
    /// <param name="line_i">Индекс строки</param>
    /// <param name="colum_i">Индекс столбца</param>
    /// <returns></returns>
    const char* getData(int line_i, int colum_i) {
        LineData* lineData = lines[line_i];
        TableCreater::LineData::ItemData* item = lines[line_i]->items;

        return item[colum_i].data;
    }

    /// <summary>
    /// Отрисовка таблицы
    /// </summary>
    void Draw() {
        DrawBorderLine();
        for (int i = 0; i < sizeLines - 1; i++) {
            DrawTextFields(lines[i], lines[i + 1]);
        }
        DrawTextFields(lines[sizeLines - 1]);
    }


    /// <summary>
    /// Загрузка данных в таблицу
    /// </summary>
    /// <param name="transports">Объект для загрузки</param>
    /// <param name="size">Количество оъектов</param>
    /// <param name="startLineIndex">Индекс первой строки для загрузки первого элемента</param>
    void UploadData(Transport** transports, int size, int startLineIndex = 0) {
        for (int i = startLineIndex; i < size + startLineIndex; i++) {
            Transport* transport = transports[i - startLineIndex];
            LineData* lineData = (LineData*)calloc(1, sizeof(LineData));
            lineData->sizeItems = new int(5);
            LineData::ItemData* items = lineData->items = (LineData::ItemData*)calloc(*lineData->sizeItems, sizeof(LineData::ItemData));


            items[0].data = _strdup(transport->type);
            items[0].pos = Start;
            items[0].widthItem = 16;

            items[1].data = _strdup(transport->number);
            items[1].pos = Start;
            items[1].widthItem = 16;


            stringstream ssLength;
            ssLength << fixed << setprecision(3) << transport->lenght;

            items[2].data = _strdup(ssLength.str().c_str());
            items[2].pos = End;
            items[2].widthItem = 30;

            items[3].data = _strdup(to_string(transport->time).c_str());
            items[3].pos = Start;
            items[3].widthItem = 25;

            items[4].data = new char[11];
            DateToChars(items[4].data, transport->date);
            items[4].pos = Centre;
            items[4].widthItem = 15;

            setElementsToLine(i, lineData);
        }
    }

    void UploadData(MyList<Transport>* list, int startLineIndex = 0) {
        for (int i = startLineIndex; i < list->getSize() + startLineIndex; i++) {
            Transport transport = list->GetDataAndToNext();
            LineData* lineData = (LineData*)calloc(1, sizeof(LineData));
            lineData->sizeItems = new int(5);
            LineData::ItemData* items = lineData->items = (LineData::ItemData*)calloc(*lineData->sizeItems, sizeof(LineData::ItemData));


            items[0].data = _strdup(transport.type);
            items[0].pos = Start;
            items[0].widthItem = 16;

            items[1].data = _strdup(transport.number);
            items[1].pos = Start;
            items[1].widthItem = 16;


            stringstream ssLength;
            ssLength << fixed << setprecision(3) << transport.lenght;

            items[2].data = _strdup(ssLength.str().c_str());
            items[2].pos = End;
            items[2].widthItem = 30;

            items[3].data = _strdup(to_string(transport.time).c_str());
            items[3].pos = Start;
            items[3].widthItem = 25;

            items[4].data = new char[11];
            DateToChars(items[4].data, transport.date);
            items[4].pos = Centre;
            items[4].widthItem = 15;

            setElementsToLine(i, lineData);
        }
    }



private:
    void DateToChars(char* chars, Date date) {

        string* buffer = new string((date.day < 10 ? "0" + to_string(date.day) : to_string(date.day)) +
            "." + (date.month < 10 ? "0" + to_string(date.month) : to_string(date.month)) + "." + to_string(date.year));
        strcpy_s(chars, sizeof(char) * 11, (*buffer).c_str());

        delete buffer;

    }

    void DrawChars(char ch, int length) {
        cout.width(length); cout.fill(ch); cout << ch;
    }

    void DrawTextFields(TableCreater::LineData* lineData, TableCreater::LineData* nextLineData = NULL) {
        for (int i = 0; i < *lineData->sizeItems; i++) {
            TableCreater::LineData::ItemData item = lineData->items[i];
            switch (item.pos) {
            case TableCreater::TextPosition::Start: {
                DrawOnStartText(item.data, item.widthItem);
            }break;
            case TableCreater::TextPosition::Centre: {
                DrawOnCenterText(item.data, item.widthItem);
            }break;
            case TableCreater::TextPosition::End: {
                DrawOnEndText(item.data, item.widthItem);
            }break;
            }
        }
        cout << '|' << endl;
        if (nextLineData == NULL) {
            DrawBorderLine();
            return;
        }
        if (*lineData->sizeItems == *nextLineData->sizeItems) DrawBorderLine(lineData);
        else DrawBorderLine();

    }

    void DrawBorderLine() {
        cout << '|';
        DrawChars('-', width - 2); cout << '|' << endl;
    }

    void DrawBorderLine(LineData* line) {
        cout << '|';
        for (int i = 0; i < *line->sizeItems; i++) {
            cout.width(line->items[i].widthItem + 1); cout.fill('-'); cout << '|';
        }
        cout << endl;
    }

    void DrawOnCenterText(char* text, int width) {
        cout << '|';
        int startIndexText = (width - strlen(text)) / 2;
        DrawChars(' ', startIndexText);
        cout << text;
        DrawChars(' ', width - (startIndexText + strlen(text)));
    }

    void DrawOnStartText(char* text, int width) {
        cout << "| ";
        cout << text;
        DrawChars(' ', width - 1 - strlen(text));
    }

    void DrawOnEndText(char* text, int width) {
        cout << "|";
        DrawChars(' ', width - 1 - strlen(text));
        cout << text << " ";
    }
};

/// <summary>
/// Добавление заголовков в таблицу
/// </summary>
/// <param name="table">Указатель на table</param>
void BaseAdd(TableCreater* table) {
    int width = table->width;
    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    TableCreater::LineData::ItemData* items = new TableCreater::LineData::ItemData;
    lineData->items = items; lineData->sizeItems = new int(1);
    items->data = _strdup("Ведомость общественного транспорта"); items->widthItem = width - 2; items->pos = TableCreater::TextPosition::Start;
    table->setElementsToLine(0, lineData);

    lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    items = (TableCreater::LineData::ItemData*)calloc(5, sizeof(TableCreater::LineData::ItemData));
    lineData->items = items; lineData->sizeItems = new int(5);
    items[0].data = _strdup("Вид транспорта"); items[0].widthItem = 16; items[0].pos = TableCreater::TextPosition::Centre;
    items[1].data = _strdup("Номер маршрута"); items[1].widthItem = 16; items[1].pos = TableCreater::TextPosition::Centre;
    items[2].data = _strdup("Протяженность маршрута (км)"); items[2].widthItem = 30; items[2].pos = TableCreater::TextPosition::Centre;
    items[3].data = _strdup("Время в дороге (мин)"); items[3].widthItem = 25; items[3].pos = TableCreater::TextPosition::Centre;
    items[4].data = _strdup("Дата"); items[4].widthItem = 15; items[4].pos = TableCreater::TextPosition::Centre;
    table->setElementsToLine(1, lineData);

}

void BaseAddEnd(TableCreater* table) {
    int width = table->width;
    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    TableCreater::LineData::ItemData* items = lineData->items = new TableCreater::LineData::ItemData;
    lineData->sizeItems = new int(1);
    items->data = _strdup("Примечание: Тр - трамвай, Тс - троллейбус, А - автобус"); items->widthItem = width - 2; items->pos = TableCreater::TextPosition::Start;

    table->setElementsToLine(table->sizeLines - 1, lineData);
}

void BaseAdd2(TableCreater* table) {
    int width = table->width;
    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    lineData->sizeItems = new int(5);
    TableCreater::LineData::ItemData* items = (TableCreater::LineData::ItemData*)calloc(*lineData->sizeItems, sizeof(TableCreater::LineData::ItemData));
    lineData->items = items;
    items[0].data = _strdup("i"); items[0].widthItem = 3; items[0].pos = TableCreater::TextPosition::Centre;
    items[1].data = _strdup("Адрес A[i]"); items[1].widthItem = 30; items[1].pos = TableCreater::TextPosition::Centre;
    items[2].data = _strdup("Строковое поле A[i]"); items[2].widthItem = 25; items[2].pos = TableCreater::TextPosition::Centre;
    items[3].data = _strdup("Адрес B[i]"); items[3].widthItem = 30; items[3].pos = TableCreater::TextPosition::Centre;
    items[4].data = _strdup("Строковое поле B[i]"); items[4].widthItem = 25; items[4].pos = TableCreater::TextPosition::Centre;
    table->setElementsToLine(2, lineData);

}

void BaseAdd1(TableCreater* table, Transport** t) {
    int width = table->width;
    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(2, sizeof(TableCreater::LineData));
    lineData->sizeItems = new int(1);
    TableCreater::LineData::ItemData* items = (TableCreater::LineData::ItemData*)calloc(*lineData->sizeItems, sizeof(TableCreater::LineData::ItemData));
    lineData->items = items;
    items->data = _strdup("Адрес первого элемента массива newTransports"); items->widthItem = width - 2; items->pos = TableCreater::TextPosition::Centre;
    table->setElementsToLine(0, lineData);

    lineData = (TableCreater::LineData*)calloc(2, sizeof(TableCreater::LineData));
    items = new TableCreater::LineData::ItemData;
    lineData->sizeItems = new int(1);
    lineData->items = items;
    stringstream ss;
    ss << &(**t);
    items->data = _strdup(ss.str().c_str()); items->widthItem = width - 2; items->pos = TableCreater::TextPosition::Start;

    table->setElementsToLine(1, lineData);

}

void ClearDataTransports(Transport** transport, int size = 1) {
    for (int i = 0; i < size; i++) {
        Transport* tr = transport[i];
        delete tr->number;
        delete tr->type;
        free(tr);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int width = 109;
    int countHeaderLines = 2;

#pragma region createTransports 
    Transport** transports = (Transport**)calloc(10, sizeof(Transport*));

    transports[0] = new Transport;
    transports[0]->type = _strdup("Тр.");
    transports[0]->number = _strdup("12");
    transports[0]->lenght = 27.550f;
    transports[0]->time = 75;
    transports[0]->date.day = 3; transports[0]->date.month = 4; transports[0]->date.year = 2022;

    transports[1] = new Transport;
    transports[1]->type = _strdup("Т-с");
    transports[1]->number = _strdup("17");
    transports[1]->lenght = 13.560f;
    transports[1]->time = 57;
    transports[1]->date.day = 3; transports[1]->date.month = 4; transports[1]->date.year = 2020;

    transports[2] = new Transport;
    transports[2]->type = _strdup("А");
    transports[2]->number = _strdup("12а");
    transports[2]->lenght = 53.300f;
    transports[2]->time = 117;
    transports[2]->date.day = 4; transports[2]->date.month = 3; transports[2]->date.year = 2022;

    for (int i = 3; i < 10; i++) {
        transports[i] = new Transport;
        transports[i]->number = new char[3];
        transports[i]->type = new char[3];
    }

    Transport** newTransports = (Transport**)calloc(10, sizeof(Transport*));
    Transport** minTime = NULL, ** maxTime = NULL;
    for (int i = 0; i < 10; i++) {
        newTransports[i] = transports[i];
        if (i > 2) continue;
        float time = transports[i]->time;
        if (minTime == NULL) minTime = &newTransports[i];
        if (maxTime == NULL) maxTime = &newTransports[i];

        if ((*minTime)->time > time) minTime = &newTransports[i];
        if ((*maxTime)->time < time) maxTime = &newTransports[i];
    }

    if (minTime != maxTime) {
        Transport* b = *minTime;
        *minTime = *maxTime;
        *maxTime = b;
    }

#pragma endregion Создание и инициализация объектов

    MyList<Transport>* list = new MyList<Transport>();
    for (int x = 0; x < 2; x++) {
        for (int i = 0; i < 3; i++) {
            list->AddElementToNext(newTransports[i]);
        }
    }
    int month;
    cout << "Введите номер месяца: "; cin >> month;
    Transport newTransport = Transport();
    newTransport.type = new char[15];
    cout << "Создание новой записи\nВид транспорта: "; cin >> newTransport.type;
    newTransport.number = new char[15];
    cout << "Номер маршрута: "; cin >> newTransport.number;
    cout << "Продолжительность маршрута: "; cin >> newTransport.lenght;
    cout << "Время в дороге: "; cin >> newTransport.time;
    Date date;
    cout << "Дата в формате {день месяц год/11 11 1111}: "; cin >> date.day >> date.month >> date.year;
    newTransport.date = date;

    int sizeEl = list->getSize();
    for (int i = 0; i < sizeEl; i++) {
        Transport t = list->getData();
        if (t.date.month == month) {
            list->AddElementToNext(new Transport(newTransport));
            list->ToNext();
        }
        list->ToNext();
    }


#pragma region UploadToFile
    FILE* file;
    fopen_s(&file, "data.bin", "wb");
    fwrite(list, sizeof(MyList<Transport>), 1, file);
    fclose(file);

    delete list;


    fopen_s(&file, "data.bin", "rb");
    fread(list, sizeof(MyList<Transport>), 1, file);
    fclose(file);

    


#pragma endregion


    TableCreater table(width, countHeaderLines + list->getSize());

#pragma region createHeader

    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    TableCreater::LineData::ItemData* items = lineData->items = new TableCreater::LineData::ItemData; lineData->sizeItems = new int(1);
    items->data = _strdup("Задание номер 3"); items->widthItem = 107; items->pos = TableCreater::Centre;

    table.setElementsToLine(0, lineData);

    lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    items = lineData->items = (TableCreater::LineData::ItemData*)calloc(3, sizeof(TableCreater::LineData::ItemData)); lineData->sizeItems = new int(3);
    items[0].data = _strdup("i"); items[0].widthItem = 5; items[0].pos = TableCreater::Centre;
    items[1].data = _strdup("Адрес элемента"); items[1].widthItem = 50; items[1].pos = TableCreater::Start;
    items[2].data = _strdup("Адрес следущего элемента"); items[2].widthItem = 50; items[2].pos = TableCreater::Start;

    table.setElementsToLine(1, lineData);


#pragma endregion Создание шапки для таблицы




#pragma region addDataToTable
    for (int i = 0; i < list->getSize(); i++) {
        TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
        TableCreater::LineData::ItemData* items = lineData->items = (TableCreater::LineData::ItemData*)calloc(3, sizeof(TableCreater::LineData::ItemData)); lineData->sizeItems = new int(3);
        stringstream ss1;
        ss1 << i;
        items[0].data = _strdup(ss1.str().c_str());
        items[0].pos = TableCreater::Centre;
        items[0].widthItem = 5;

        stringstream ss2;
        ss2 << list->node;
        items[1].data = _strdup(ss2.str().c_str());
        items[1].pos = TableCreater::Start;
        items[1].widthItem = 50;

        stringstream ss3;
        ss3 << list->node->next;
        items[2].data = _strdup(ss3.str().c_str());
        items[2].pos = TableCreater::Start;
        items[2].widthItem = 50;

        list->ToNext();

        table.setElementsToLine(i + 2, lineData);
    }

#pragma endregion Добавление элементов из списка в таблицу по заданию

    table.Draw();

    table.ClearData();
    table.CreateTable(list->getSize() + 3, 108);


    BaseAdd(&table);
    table.UploadData(list, 2);
    BaseAddEnd(&table);
    cout << endl << endl;
    table.Draw();
    ClearDataTransports(transports, 10);
    free(newTransports);
    return 0;

}