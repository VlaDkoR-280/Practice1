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

struct Data {
    char* data1;
    int width1;
};

class TableCreater {
public:
    int width;
    int sizeLines;
    struct LineData {
        int* sizeItems;
        struct ItemData {
            char* data;
            int* widthItem;
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

    void setElementsToLine(int indexLine, Data* itemsData, int sizeItems) {
        (this->lines[indexLine].sizeItems) = new int(sizeItems);
        this->lines[indexLine].items = new LineData::ItemData[sizeItems];
        LineData::ItemData* ptr = this->lines[indexLine].items;
        for (int i = 0; i < sizeItems; i++) {
            ((ptr + i)->data) = ((itemsData + i)->data1);
            ((ptr + i)->widthItem) = new int((itemsData + i)->width1);
        }
        return;
    }


    const char* getData(int line_i, int colum_i) {
        TableCreater::LineData::ItemData* item = this->lines[line_i].items;

        return item[colum_i].data;
    }

};

void BaseAdd(TableCreater table, int width) {
    Data data[5];
    data[0].data1 = _strdup("Ведомость общественного транспорта"); data[0].width1 = width - 2;
    table.setElementsToLine(0, data, 1);

    data[0].data1 = _strdup("Вид транспорта"); data[0].width1 = 15;
    data[1].data1 = _strdup("Номер маршрута"); data[1].width1 = 15;
    data[2].data1 = _strdup("Протяженность маршрута (км)"); data[2].width1 = 30;
    data[3].data1 = _strdup("Время в дороге (мин)"); data[3].width1 = 25;
    data[4].data1 = _strdup("Дата"); data[4].width1 = 15;
    table.setElementsToLine(1, data, 5);

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int width = 100;
    TableCreater table(width, 6);

    BaseAdd(table, width);

   
    
    cout << table.getData(0, 0);

    return 0;

}
