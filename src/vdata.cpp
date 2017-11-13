/*
 *
 * Vdata module for BDB
 *
 */
#include <stdio.h>
#include <db.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
//#define DATABASE "empx.db"
#include "emp.h"

struct DayZ DDisplay(int day_num)
{
   DBT key, data;
   DBC *cursor;
   DB *dbp;
   int ret;
   float xpenZ = 0.;
   DayZ DZ = {0,0.} ;
   struct employeeRecord emp;

   ret = db_create(&dbp, NULL, 0);
   if (ret != 0)
   {
      perror("create");
      return DZ;
   }

   ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE, DB_RDONLY, 0);
   if (ret != 0)
   {
      perror("open: ");
      return DZ;
   }

   ret = dbp->cursor(dbp, NULL, &cursor, 0);
   if (ret != 0)
   {
      perror("cursor: ");
      return DZ;
   }

   memset(&key, 0, sizeof(key));
   memset(&data, 0, sizeof(data));

   key.flags = DB_DBT_USERMEM;
   data.flags = DB_DBT_USERMEM;

   key.data = (char *)malloc(sizeof(key));
   key.ulen = sizeof(key);
   data.data = (char *)malloc(sizeof(data));
   data.ulen = sizeof(emp);

   memset(key.data, 0, sizeof(key.data));
   memset(data.data, 0, sizeof(data.data));

   data.data = &emp;
   data.size = sizeof(emp);
   data.flags = DB_DBT_USERMEM;
/*
//----------------------------------------
   ret = cursor->get(cursor, &key, &data, DB_NEXT);
   if (ret !=0) {
     fprintf(stderr, "Failed CURSOR %s: %s\n", DATABASE, db_strerror(ret));
     free(key.data);
     free(data.data);

     return 1;
   }
   printw("%d Tjoijion", ret);
   printw("RR%d - %d,%s   $%.2lf\n", emp.empid, emp.large, emp.note, emp.xpen);
//----------------------------------------
*/

//while ((ret = dbcp->get(dbcp, &key, &data, DB_NEXT)) == 0)
//   printw("TTTTTT\n");
   while((ret = cursor->c_get(cursor, &key, &data, DB_NEXT)) == 0)
   {
//         printw("%d - %d,%s   $%.2lf\n", emp.empid, emp.large, emp.note, emp.xpen);
          if (emp.empid > 86400) {
            DZ.Z += emp.xpen;
          } else if (emp.empid > 86400) {
            DZ.Z += emp.xpen;
          } else if (emp.empid > 86400) {
            DZ.Z += emp.xpen;
          } else if (emp.empid > 86400) {
            DZ.Z += emp.xpen;
          }
   }

   free(key.data);
//   free(data.data);

   cursor->c_close(cursor);
   dbp->close(dbp, 0);
//   return 0;
   return DZ;
}

struct Days display(int mode, int t1, int t2, int t3, int t4)
{
   DBT key, data;
   DBC *cursor;
   DB *dbp;
   int ret;
   float xpenZ = 0.;
   Days DS = {0., 0., 0., 0.} ;
//   float xpen1 = 0.;
//   float xpen2 = 0.;
   struct employeeRecord emp;

   ret = db_create(&dbp, NULL, 0);
   if (ret != 0)
   {
      perror("create");
      return DS;
   }

   ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_BTREE, DB_RDONLY, 0);
   if (ret != 0)
   {
      perror("open: ");
      return DS;
   }

   ret = dbp->cursor(dbp, NULL, &cursor, 0);
   if (ret != 0)
   {
      perror("cursor: ");
      return DS;
   }

   memset(&key, 0, sizeof(key));
   memset(&data, 0, sizeof(data));

   key.flags = DB_DBT_USERMEM;
   data.flags = DB_DBT_USERMEM;

   key.data = (char *)malloc(sizeof(key));
   key.ulen = sizeof(key);
   data.data = (char *)malloc(sizeof(data));
   data.ulen = sizeof(emp);

   memset(key.data, 0, sizeof(key.data));
   memset(data.data, 0, sizeof(data.data));

   data.data = &emp;
   data.size = sizeof(emp);
   data.flags = DB_DBT_USERMEM;
/*
//----------------------------------------
   ret = cursor->get(cursor, &key, &data, DB_NEXT);
   if (ret !=0) {
     fprintf(stderr, "Failed CURSOR %s: %s\n", DATABASE, db_strerror(ret));
     free(key.data);
     free(data.data);

     return 1;
   }
   printw("%d Tjoijion", ret);
   printw("RR%d - %d,%s   $%.2lf\n", emp.empid, emp.large, emp.note, emp.xpen);
//----------------------------------------
*/

//while ((ret = dbcp->get(dbcp, &key, &data, DB_NEXT)) == 0)
//   printw("TTTTTT\n");
   while((ret = cursor->c_get(cursor, &key, &data, DB_NEXT)) == 0)
   {
      if (mode == 1) {
         printw("%d - %d,%s   $%.2lf\n", emp.empid, emp.large, emp.note, emp.xpen);
      } else if (mode == 2) {
         xpenZ += emp.xpen;        
      } else if (mode == 3) {
          if (emp.empid > t1) {
            DS.xpen1 += emp.xpen;
          } else if (emp.empid > t2) {
            DS.xpen2 += emp.xpen;
          } else if (emp.empid > t3) {
            DS.xpen3 += emp.xpen;
          } else if (emp.empid > t4) {
            DS.xpen4 += emp.xpen;
          }
      }
   }
   
   if (mode == 2) {
      printw("Tot: %2.2f\n",xpenZ);
   }
   if (mode == 3) {
      printw("XTotx: %3.2f , %3.2f\n",DS.xpen2,DS.xpen1);
   }


   free(key.data);
//   free(data.data);

   cursor->c_close(cursor);
   dbp->close(dbp, 0);
//   return 0;
   return DS;
}
