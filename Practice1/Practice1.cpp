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
    int width;
    int sizeLines;
    struct LineData {
        int* sizeItems;
        struct ItemData {
            char* data;
            int widthItem;
        }* items;
    }* lines;


    TableCreater(int width, int sizeLines) {
        this->width = width; this->sizeLines = sizeLines;
        lines = new LineData[sizeLines];
    }

    void setElementsToLine(int indexLine, LineData::ItemData* itemsData, int sizeItems) {
        (this->lines[indexLine].sizeItems) = new int(sizeItems);
        this->lines[indexLine].items = new LineData::ItemData[sizeItems];
        LineData::ItemData* ptr = this->lines[indexLine].items;
        for (int i = 0; i < sizeItems; i++) {
            ((ptr + i)->data) = ((itemsData + i)->data);
            ((ptr + i)->widthItem) = ((itemsData + i)->widthItem);
        }
        return;
    }



    const char* getData(int line_i, int colum_i) {
        TableCreater::LineData::ItemData* item = this->lines[line_i].items;

        return item[colum_i].data;
    }


    void Draw() {
        indexSplits = (int*)calloc(5, sizeof(int*));
        DrawStartLine();
        DrawNullLine(this->lines[0]);

    }

private:
    int* indexSplits;
    void DrawChars(char ch, int length) {
        for (int i = 0; i < length; i++); cout << ch;
    }
    void DrawNullLine() {
        cout << '|';
        DrawChars(' ', width - 2);
        cout << '|' << endl;
    }


    void DrawNullLine(TableCreater::LineData lineData) {
        cout << '|';
        int indexEl = 0;
        //lineData->items;
        for (int i = 0; i < *lineData.sizeItems; i++) {
            DrawChars(' ', lineData.items[i].widthItem); cout << '|';
        }
    }

    void DrawNullEndLine(TableCreater::LineData* lineData) {
        cout << '|';
        int indexEl = 0;
        //lineData->items;
        for (int i = 0; i < *lineData->sizeItems; i++) {
            DrawChars('_', lineData->items[i].widthItem); cout << '|';
        }
    }

    void DrawNullEndLine() {
        cout << '|';
        for (int i = 0; i < this->width - 2; i++) cout << "_";
        cout << '|' << endl;
    }
    void DrawStartLine() {
        cout.width(this->width + 1); cout.fill('_'); cout << "\n";
    }
    void DrawOnCenterText(char* text, int width) {
        DrawNullLine();
        cout << '|';
        int startIndexText = (width - strlen(text)) / 2;
        for (int i = 0; i < startIndexText; i++) {
            cout << " ";
        }
        for (int i = startIndexText; i < startIndexText + strlen(text); i++) {
            cout << text[i - startIndexText];
        }
        for (int i = startIndexText + strlen(text); i < this->width - 2; i++) {
            cout << " ";
        }
        
    }
    void DrawOnStartText(char* text, int width) {
        DrawNullLine();
        cout << "| ";
        for (int i = 0; i < strlen(text); i++) {
            cout << text[i];
        }
        for (int i = strlen(text); i < width - 2; i++) {
            cout << " ";
        }

    }
    void DrawOnEndText(char* text, int width) {
        DrawNullLine();
        cout << "|";
        for (int i = 0; i < width - 2 - strlen(text); i++) {
            cout << " ";
        }
        cout << text << " ";
        
    }

};

void BaseAdd(TableCreater table, int width) {
    //TableCreater::LineData::ItemData data[5];
    TableCreater::LineData::ItemData* data = (TableCreater::LineData::ItemData*)calloc(5, sizeof(TableCreater::LineData::ItemData));
    data[0].data = _strdup("Ведомость общественного транспорта"); data[0].widthItem = width - 2;
    table.setElementsToLine(0, data, 1);

    data[0].data = _strdup("Вид транспорта"); data[0].widthItem = 15;
    data[1].data = _strdup("Номер маршрута"); data[1].widthItem = 15;
    data[2].data = _strdup("Протяженность маршрута (км)"); data[2].widthItem = 30;
    data[3].data = _strdup("Время в дороге (мин)"); data[3].widthItem = 25;
    data[4].data = _strdup("Дата"); data[4].widthItem = 15;
    table.setElementsToLine(1, data, 5);
    free(data);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int width = 106;
    TableCreater table(width, 6);

    BaseAdd(table, width);
    char* t = (char*)"test";
    table.Draw();
    cout << strlen(t);
    
    //cout << table.getData(1, 1);

    return 0;

}
