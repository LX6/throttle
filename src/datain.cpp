/*
 *
 * Professional Linux Programming - Adding a new employee record
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <db.h>
#include <time.h>

#include "emp.h"

int main(int argc, char**argv)
{
   DBT key, data;
   DB *db; // DB handle
   int ret;
   struct employeeRecord emp;

   // Initialize our DB handle
   ret = db_create(&db, NULL, 0);
   if (ret != 0)
   {
      fprintf(stderr, "Failed to initialize the database handle: %s\n", db_strerror(ret));
      return 1;
   }

   // Open the existing DATABASE file or create a new one if it doesn't exist.
   ret = db->open(db, NULL, DATABASE, NULL, DB_BTREE, DB_CREATE, 0);
   if (ret != 0)
   {
      fprintf(stderr, "Failed to open database file %s: %s\n", DATABASE, db_strerror(ret));
      return 1;
   }

   while(1)
   {
      printf("Enter ID: ");
      scanf("%d", &emp.empid);
      if (emp.empid == 0)
         break;
      printf("Enter BigSma: ");
      scanf("%d", &emp.large);
      printf("Enter Note: ");
      scanf("%s", &emp.note);
      printf("Enter xpen: ");
      scanf("%f", &emp.xpen);

      memset(&key, 0, sizeof(DBT));
      memset(&data, 0, sizeof(DBT));

      if (emp.empid < 1500000407) {
         emp.empid = time(NULL);
      }
      key.data = &(emp.empid);
      key.size = sizeof(emp.empid);
      data.data = &emp;
      data.size = sizeof(emp);

      if (argc != 2) {
         ret = db->put(db, NULL, &key, &data, DB_NOOVERWRITE);
      } else {
         ret = db->put(db, NULL, &key, &data, DB_NOOVERWRITE);
//         ret = db->put(db, NULL, &key, &data, DB_CURRENT);
      }

      if (ret != 0)
      {
         printf("Employee ID exists\n");
      }
   }

   db->close(db, 0);
   return 0;
}


