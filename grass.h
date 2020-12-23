// NOTE: grass = 0, road = 1

#ifndef GRASS_H
#define GRASS_H

class grass {
  public:
    grass();
    void create();   // 亂數分布障礙物 ,參數輸入1表示要生成障礙物，0表示空行
    int& send();         // 傳出該行障礙物分布
    void receive(int&);  // 接收上行障礙物分布
    void reset();        // 歸零

  private:
    int grass_num;  // 判斷該列有幾個 grass
    int grass_position;
    int road[5];
};

#endif