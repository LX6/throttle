#define DATABASE "empx.db"

struct Days{
    float xpen1;
    float xpen2;
    float xpen3;
    float xpen4;
};

struct DayZ{
    int ordnum;
    float Z;
};

struct employeeRecord{
   int empid;
   int large; // 0 or 1
   char note[55];
   float xpen; //xpense
};

