#include <iostream>
#include <windows.h>
using namespace std;

struct Transport {
    char type[3];
    char number[3];
    float lenght;
    short time;
    short day;
    short mounth;
    short year;
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


    TableCreater(int width, int sizeLines) {
        this->width = width; this->sizeLines = sizeLines;
        lines = (TableCreater::LineData**)calloc(this->sizeLines, sizeof(TableCreater::LineData**));
        /*for (int i = 0; i < sizeLines; i++) {
            lines[i] = new LineData;
        }*/
        
    }

    ~TableCreater() {
        ClearData();
    }

    /// <summary>
    /// Очистка lines
    /// </summary>
    void ClearData() {
        
    }

    /// <summary>
    /// Очистка таблицы
    /// </summary>
    /// <param name="width">Ширина таблицы, 0 - останется прежним</param>
    /// <param name="sizeLines">Кол-во строк в таблице, 0 - останется прежним</param>
    void ClearTable(int width = 0, int sizeLines = 0) {
        if (width >= 0) this->width = width;
        if (sizeLines >= 0) this->sizeLines = sizeLines;

        ClearData();
        lines = (TableCreater::LineData**)calloc(this->sizeLines, sizeof(TableCreater::LineData**));
        for (int i = 0; i < sizeLines; i++) {
            lines[i] = new LineData;
        }
    }



    /*void setElementsToLine(int indexLine, LineData::ItemData* itemsData, int sizeItems) {
        lines[indexLine]->sizeItems = new int(sizeItems);
        lines[indexLine]->items = itemsData;
    }*/

    void setElementsToLine(int indexLine, LineData* lineData) {
        lines[indexLine] = lineData;
    }


    const char* getData(int line_i, int colum_i) {
        LineData* lineData = lines[line_i];
        TableCreater::LineData::ItemData* item = lines[line_i]->items;

        return item[colum_i].data;
    }


    void Draw() {
        DrawBorderLine();
        for (int i = 0; i < sizeLines; i++) {
            DrawTextFields(lines[i]);
        }
        //DrawLine(this->lines[1]);

    }

private:
    void DrawChars(char ch, int length) {
        cout.width(length); cout.fill(ch); cout << ch;
        
        //for (int i = 0; i < length; i++); cout << ch;
    }
    

     



    void DrawTextFields(TableCreater::LineData* lineData) {
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
        DrawBorderLine(lineData);
    }


    
    void DrawBorderLine() {
        DrawChars('-', width); cout << endl;

    }

    void DrawBorderLine(LineData* line) {
        cout << '|';
        for (int i = 0; i < *line->sizeItems; i++) {
            int nullWidth = line->items[i].widthItem;
            for (int j = 0; j < nullWidth; j++) {
                cout << '-';
            }
            cout << '|';
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
        for (int i = 0; i < width - 2 - strlen(text); i++) {
            cout << " ";
        }
        cout << text << " ";
        
    }

};

void BaseAdd(TableCreater table, int width) {
    //TableCreater::LineData::ItemData data[5];
    TableCreater::LineData::ItemData* data = (TableCreater::LineData::ItemData*)calloc(1, sizeof(TableCreater::LineData::ItemData));
    data->data = _strdup("Ведомость общественного транспорта"); data->widthItem = width - 2; data->pos = TableCreater::TextPosition::Start;
    table.setElementsToLine(0, data, 1);


    data = (TableCreater::LineData::ItemData*)calloc(5, sizeof(TableCreater::LineData::ItemData));
    data[0].data = _strdup("Вид транспорта"); data[0].widthItem = 16; data[0].pos = TableCreater::TextPosition::Centre;
    data[1].data = _strdup("Номер маршрута"); data[1].widthItem = 16; data[1].pos = TableCreater::TextPosition::Centre;
    data[2].data = _strdup("Протяженность маршрута (км)"); data[2].widthItem = 30; data[2].pos = TableCreater::TextPosition::Centre;
    data[3].data = _strdup("Время в дороге (мин)"); data[3].widthItem = 25; data[3].pos = TableCreater::TextPosition::Centre;
    data[4].data = _strdup("Дата"); data[4].widthItem = 15; data[4].pos = TableCreater::TextPosition::Centre;
    table.setElementsToLine(1, data, 5);

    //free(data);
}

void BaseAdd2(TableCreater table, int width) {
    //TableCreater::LineData::ItemData data[5];
    TableCreater::LineData* lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    TableCreater::LineData::ItemData* items = new TableCreater::LineData::ItemData;
    lineData->items = items; lineData->sizeItems = new int(1);
    items->data = _strdup("Ведомость общественного транспорта"); items->widthItem = width - 2; items->pos = TableCreater::TextPosition::Start;
    table.setElementsToLine(0, lineData);


    lineData = (TableCreater::LineData*)calloc(1, sizeof(TableCreater::LineData));
    items = (TableCreater::LineData::ItemData*)calloc(5, sizeof(TableCreater::LineData::ItemData));
    lineData->items = items; lineData->sizeItems = new int(5);
    items[0].data = _strdup("Вид транспорта"); items[0].widthItem = 16; items[0].pos = TableCreater::TextPosition::Centre;
    items[1].data = _strdup("Номер маршрута"); items[1].widthItem = 16; items[1].pos = TableCreater::TextPosition::Centre;
    items[2].data = _strdup("Протяженность маршрута (км)"); items[2].widthItem = 30; items[2].pos = TableCreater::TextPosition::Centre;
    items[3].data = _strdup("Время в дороге (мин)"); items[3].widthItem = 25; items[3].pos = TableCreater::TextPosition::Centre;
    items[4].data = _strdup("Дата"); items[4].widthItem = 15; items[4].pos = TableCreater::TextPosition::Centre;
    table.setElementsToLine(1, lineData);

    //free(data);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int width = 108;
    TableCreater table(width, 2);

    BaseAdd2(table, width);
    //cout << table.getData(1, 1);
    table.Draw();

    return 0;

}

/*
 ---------------------------------
| test        | test2             |
|---------------------------------|
| test        | test2             |
|---------------------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|

 
 _________________________________
| test        | test2             |
|_____________|___________________|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------|
| test        | test2             |
|-------------|-------------------| 
 
 
 
 
 */