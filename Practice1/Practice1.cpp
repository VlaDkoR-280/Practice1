﻿#include <iostream>
#include <windows.h>
#include <sstream>
#include <charconv>
#include <string>
#include "Practice1.h"
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
        }* items;
    }** lines;

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
        for (int i = 0; i < sizeLines; i++) {
            delete (lines[i]->sizeItems);

            for (int j = 0; j < *lines[i]->sizeItems; j++) {
                delete lines[i]->items[j].data;
            }
            free(lines[i]->items);

            free(lines[i]);
        }
        free(lines);
    }

    /// <summary>
    /// Изменение данных строки
    /// </summary>
    /// <param name="indexLine">индекс строки</param>
    /// <param name="lineData">Данные строки</param>
    void setElementsToLine(int indexLine, LineData* lineData) {
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
            DrawTextFields(lines[i], lines[i+1]);
        }
        DrawTextFields(lines[sizeLines - 1]);
    }

    
    /// <summary>
    /// Загрузка данных в таблицу
    /// </summary>
    /// <param name="transports">Объект для загрузки</param>
    /// <param name="size">Количество оъектов</param>
    /// <param name="startLineIndex">Индекс первой строки для загрузки первого элемента</param>
    void UploadData(Transport* transports, int size, int startLineIndex = 0) {
        for (int i = startLineIndex; i < size + startLineIndex; i++) {
            Transport transport = transports[i - startLineIndex];
            LineData* lineData = (LineData*) calloc(1, sizeof(LineData));
            lineData->sizeItems = new int(5);
            LineData::ItemData* items = lineData->items = (LineData::ItemData*)calloc(*lineData->sizeItems, sizeof(LineData::ItemData));
            

            items[0].data = transport.type;
            items[0].pos = Start;
            items[0].widthItem = 16;

            items[1].data = transport.number;
            items[1].pos = Start;
            items[1].widthItem = 16;
            
            items[2].data = _strdup(to_string(transport.lenght).c_str());
            items[2].pos = End;
            items[2].widthItem = 30;

            items[3].data = items[2].data = _strdup(to_string(transport.time).c_str());
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
        if(*lineData->sizeItems == *nextLineData->sizeItems) DrawBorderLine(lineData);
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

    table->setElementsToLine(5, lineData);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int width = 108;
    TableCreater table(width, 6);
    
    BaseAdd(&table);
    
    Transport* transports = (Transport*) calloc(3, sizeof(Transport));
    transports[0].type = _strdup("Тр.");
    transports[0].number = _strdup("12");
    transports[0].lenght = 27.550f;
    transports[0].time = 75;
    transports[0].date.day = 3; transports[0].date.month = 4; transports[0].date.year = 2022;

    transports[1].type = _strdup("Т-с");
    transports[1].number = _strdup("17");
    transports[1].lenght = 13.560f;
    transports[1].time = 57;
    transports[1].date.day = 3; transports[1].date.month = 4; transports[1].date.year = 2020;

    transports[2].type = _strdup("А");
    transports[2].number = _strdup("12а");
    transports[2].lenght = 53.300f;
    transports[2].time = 117;
    transports[2].date.day = 4; transports[2].date.month = 3; transports[2].date.year = 2022;
         
    table.UploadData(transports, 3, 2);
    BaseAddEnd(&table);


    table.Draw();

    

    return 0;

}