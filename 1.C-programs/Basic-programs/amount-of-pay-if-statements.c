#include <stdio.h>
#include <stdlib.h>
/* the program asks the user to enter number of hours worked
the program should display gross pay, the taxes, and the net pay
the following assumptions are made
basic pay rate $12 /hr
overtime pay rate (in excess of 40 hours) $18 /hr
Tax rate:
15% for first $300
20% for next $150
25% for the rest
*/

int main()
{
  int work_hours,basic_pay,overtime_pay;
  float gross_pay;
  printf("Enter the number of hours of work:");
  scanf("%d",&work_hours);
  basic_pay = 12;
  overtime_pay = 18;

 // Calculating gross pay
  if (work_hours<=40)
  {
      gross_pay = work_hours * basic_pay;
  }
    else if (work_hours>40)
    {
      gross_pay = ((work_hours - 40)*overtime_pay) + (40 * basic_pay);
    }

 // Calculate taxes
  float total_taxes;
  if (gross_pay<=300)
  {
      total_taxes = (gross_pay * 0.15);
  }
  else if (gross_pay>300 && gross_pay<=450)
  {
      total_taxes = ((gross_pay - 300) * 0.20) + (300 * 0.15);
  }
  else if (gross_pay > 450)
  {
      total_taxes = ((gross_pay - 450) * 0.25) + (150 * 0.20) + (300 * 0.15);
  }

 //Calculating net payment
  float net_pay;
  net_pay = gross_pay - total_taxes;

  //display the following

  printf("gross pay is: %lf\n",gross_pay);
  printf("total taxes are: %f\n",total_taxes);
  printf("net pay for the week is: %f\n",net_pay);

    return 0;
}
