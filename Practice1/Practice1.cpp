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


    void addLineData(char* data[40], int* width, int colums, int indexLine) {
        TableCreater::LineData::ItemData* items = (TableCreater::LineData::ItemData*)malloc(colums);
        for (int i = 0; i < colums; i++) {
            items->data = _strdup(data[i]);
            items->widthItem = new int(width[i]);
        }
        this->setElementsToLine(indexLine, items, colums);
        //free(items);
    }

    void addLineData(Data data[5], int colums, int indexLine) {
        TableCreater::LineData::ItemData* items = (TableCreater::LineData::ItemData*)malloc(colums);
        for (int i = 0; i < colums; i++) {
            items->data = data[i].data1;
            items->widthItem = new int(data[i].width1);
        }
        this->setElementsToLine(indexLine, data, colums);
        //free(items);
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
    //table.addLineData(data, 1, 0);
    data[0].data1 = _strdup("Вид транспорта"); data[0].width1 = 15;
    data[1].data1 = _strdup("Номер маршрута"); data[1].width1 = 15;
    data[2].data1 = _strdup("Протяженность маршрута (км)"); data[2].width1 = 30;
    data[3].data1 = _strdup("Время в дороге (мин)"); data[3].width1 = 25;
    data[4].data1 = _strdup("Дата"); data[4].width1 = 15;
    table.setElementsToLine(1, data, 5);
    //table.addLineData(data, 5, 1);
    /*char* data[40] = { (char*)"Ведомость общественного транспорта" };
    int* dwidth = new int[5];*/


    //table.addLineData(data, new int(width - 2), 1, 0);


    
    /*char* data2[40] = { (char*)"Вид транспорта", (char*)"Номер маршрута", (char*)"Протяженность маршрута (км)", (char*)"Время в дороге (мин)", (char*)"Дата" };  
    dwidth[0] = 15; dwidth[1] = 15; dwidth[2] = 30;  dwidth[3] = 25; dwidth[4] = 15;
    
    table.addLineData(data2, dwidth, 5, 1);*/
    
    
    /*data[1] = (char*)_strdup("Номер маршрута"); dwidth[1] = 15;
    data[2] = (char*)_strdup("Протяженность маршрута (км)"); dwidth[2] = 30;
    data[3] = (char*)_strdup("Время в дороге (мин)"); dwidth[3] = 25;
    data[3] = (char*)_strdup("Дата"); dwidth[4] = 15;
    table.addLineData(data, dwidth, 5);*/
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int width = 100;
    TableCreater table(width, 6);

    BaseAdd(table, width);



    
    
    cout << table.getData(0, 0);

    /*TableCreater::LineData::ItemData* items = (TableCreater::LineData::ItemData*) malloc(1);*/
    /*items->data = _strdup("Ведомость общественного транспорта");
    items->widthItem = new int(width - 2);
    table.setElementsToLine(0, items, 1);*/

    //items = (TableCreater::LineData::ItemData*) realloc(items, 5);
    //items[0].data = _strdup("Вид транспорта"); items[0].widthItem = 15;
    //items[1].data = _strdup("Номер маршрута"); items[0].widthItem = 15;
    //items[2].data = _strdup("Протяженность маршрута (км)"); items[2].widthItem = 30;
    //items[3].data = _strdup("Время в дороге (мин)"); items[3].widthItem = 25;
    //items[4].data = _strdup("Дата"); items[4].widthItem = 15;

    //table.setElementsToLine(1, items, 5);


    //free(items);
    //TableCreater::LineData::ItemData* item = table.lines[0].items;
    //cout << items[0].data;
    return 0;

}
