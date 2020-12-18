// NOTE: grass = 0, road = 1

#ifndef GRASS_H
#define GRASS_H

class grass {
  public:
    grass();
    void create();       // 亂數分布障礙物
    int& send();         // 傳出該行障礙物分布
    void receive(int&);  // 接收上行障礙物分布

  private:
    bool have_grass;  // 判斷該列有沒有 grass
    int grass_num;    // 判斷該列有幾個 grass
    int road[5];
};

#endif