
Conversation opened. 1 read message. 

Skip to content
Using Gmail with screen readers
dspd.assignment@gmail.com 
2 of 17
BT20CSE085_A2

BT20CSE085_M. HEMANTH <mbannu08@gmail.com>
Attachments
Wed, Apr 6, 2022, 9:34 PM
to dspd.assignment


 One attachment
  •  Scanned by Gmail
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define SIZE 50
typedef enum{SUCCESS,FAILURE} statusCode;
typedef enum{FALSE,TRUE} boolean;
typedef struct personalNode personal;
typedef struct professionalNode professional;
typedef struct phonebookNode phonebook;


struct professionalNode{
  char firstName[SIZE];
  char lastName[SIZE];
  long long int phoneNumber;
  long long int officeNumber;
  professional* next;
  professional* prev;
};


struct personalNode{
  char firstName[SIZE];
  char lastName[SIZE];
  long long int phoneNumber;
  personal* next;
  personal* prev;
};


struct phonebookNode{
  char ownerName[SIZE];
  char email[SIZE];
  char address[SIZE];
  personal* personalHeader;
  professional* professionalHeader;
  int hours;
  int minutes;
  phonebook* next;
  phonebook* prev;
};

void printpersonal(personal* lptr)                                        
{
    printf("first name:%s\n",lptr->firstName);
    printf("last name:%s\n",lptr->lastName);
    printf("mobile number:%lld\n",lptr->phoneNumber);
}


statusCode insert_professional(professional** head)
{
  statusCode ret_val = SUCCESS;
  professional* nptr;
  nptr = (professional*) malloc(sizeof(professional));
  if(nptr==NULL)
  {
    ret_val = FAILURE;
  }
  else
  {
    printf("Enter the contact detials\n");
    printf("_________________________\n");
    printf("Enter the first name:");
    scanf("%s",nptr->firstName);
    printf("Enter the last name:");
    scanf("%s",nptr->lastName);
    printf("Enter phone number:");
    scanf("%lld",&nptr->phoneNumber);
    printf("Enter office number:");
    scanf("%lld",&nptr->officeNumber);

    nptr->next = (*head);
    nptr->prev = NULL;
    if(*head!=NULL)
    {
      (*head)->prev = nptr;
    }
    *head = nptr;
  }

    return ret_val;
}

void printprofessional(professional* lptr)
{
    printf("first name:%s\n",lptr->firstName);
    printf("last name:%s\n",lptr->lastName);
    printf("mobile number:%lld\n",lptr->phoneNumber);
    printf("office number:%lld\n",lptr->officeNumber);
}

void edit_Professional_Contact(professional* lptr)
{
  printf("The contact details are\n");
  printf("---------------------------\n");
  printprofessional(lptr);
  printf("Enter the new details\n");
  printf("--------------------------\n");
  printf("Enter the first name:");
  scanf("%s",lptr->firstName);
  printf("Enter the last name:");
  scanf("%s",lptr->lastName);
  printf("Enter phone number:");
  scanf("%lld",&lptr->phoneNumber);
  printf("Enter the office number:");
  scanf("%lld",&lptr->officeNumber);

}

void delete_Professional_Contact(professional* lptr,professional**head)
{
  if(*head == lptr)
  {
    *head = lptr->next;
  }
  if(lptr->next!=NULL)
  {
    lptr->next->prev = lptr->prev;
  }
  if(lptr->prev!=NULL)
  {
    lptr->prev->next = lptr->next;
  }

}

professional* search_Professional_Contact_by_number(long long int number, professional* list_ptr)
{
  professional* lptr;
  lptr = list_ptr;

  while(lptr!=NULL)
  {
    if(lptr->phoneNumber==number) return lptr;
    lptr = lptr->next;
  }

  return lptr;
}

void search_Professional_by_name(char* firstName,char* lastName,professional* list_ptr)
{
  professional* lptr;
  statusCode sc = FAILURE;
  lptr = list_ptr;
  if(sc == FAILURE)
  {
    printf("sorry there is no contact with name %s %s\n",firstName,lastName );
  }
  while(lptr!=NULL)
  {
    if(strcmp(lptr->firstName,firstName)==0 &&strcmp(lptr->lastName,lastName)==0)
    {
      printf("_____________________\n");
      printprofessional(lptr);
      printf("______________________\n");
      sc = SUCCESS;
    }
    lptr = lptr->next;
  }
  
}

void displayProfessional(professional* list_ptr)
{
  professional* lptr;
  lptr = list_ptr;
  printf("##########\n");
  printf("PROFESSIONAL CONTACT LIST\n");
  printf("##########\n");
  while(lptr!=NULL)
  {
    printf("___________________\n");
    printprofessional(lptr);
    printf("____________________\n");
    lptr = lptr->next;
  }

}

professional*splitProfessional(professional*head)
{
    professional*first = head,*second = head;
    while (first->next && first->next->next)
    {
        first = first->next->next;
        second = second->next;
    }
    professional*temp = second->next;
    second->next = NULL;
    return temp;
}

boolean comp_professional(professional*first,professional* second)
{
 
   if(strcmp(first->firstName,second->firstName)==0)
  {
    if(strcmp(first->lastName,second->lastName)<0)
    {
      return TRUE;
    }
    else if(strcmp(first->lastName,second->lastName)==0)
    {
      if(first->phoneNumber<second->phoneNumber)
      {
        return TRUE;
      }
    }
  } 
  else if(strcmp(first->firstName,second->firstName)<0)
  {
    return TRUE;
  }
  return FALSE;
}

professional*mergeProfessional(professional*first, professional*second)
{
	
    if (second==NULL)
    {
      return first;
    }

    if (first==NULL)
    {
      return second;
    }


    if (comp_professional(first,second))
    {
        first->next = mergeProfessional(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = mergeProfessional(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

professional* s_Professional(professional* head)
{
  if(head==NULL||head->next == NULL)
  {
    return head;
  }
  professional* temp = splitProfessional(head);

  head = s_Professional(head);
  temp = s_Professional(temp);

  return mergeProfessional(head,temp);

}

professional* cr_ProfessionalList(size_t number)
{
  professional* list_ptr=NULL;
  statusCode sc;
  int i;
  for(i=1; i<=number; i++)
  {
    sc = insert_professional(&list_ptr);
    if(sc==FAILURE)
    {
      return NULL;
    }
  }

  return list_ptr;

}

void pushProfessional(professional** resultHead, professional* lptr)
{
  professional* newNode= (professional*)malloc(sizeof(professional));
  strcpy(newNode->firstName,lptr->firstName);
  strcpy(newNode->lastName,lptr->lastName);
  newNode->phoneNumber = lptr->phoneNumber;
  newNode->officeNumber = lptr->officeNumber;
  newNode->next = (*resultHead);
  (*resultHead) = newNode;
}

boolean PresentProfessional(professional* head, professional* ptr)
{
  professional* lptr = head;
  while(lptr!=NULL)
  {
    if(strcmp(lptr->firstName ,ptr->firstName)==0 && strcmp(lptr->lastName ,ptr->lastName)==0 && lptr->phoneNumber == ptr->phoneNumber && lptr->officeNumber == ptr->officeNumber)
    {
      return TRUE;
    }
    lptr= lptr->next;
  }

  return FALSE;
}

professional* u_Professional(professional* first, professional* second)//union
{

    professional* result = NULL;
    professional *ptr1 = first, *ptr2 = second;
	
	while (ptr2 != NULL)
	{
        if (!PresentProfessional(result, ptr2))
            pushProfessional(&result, ptr2);
        ptr2 = ptr2->next;
    }
    while (ptr1 != NULL) 
	{
        pushProfessional(&result, ptr1);
        ptr1 = ptr1->next;
    }

   

    return result;
}

void delete_ProfessionalDuplicates(professional* head)
{
  if (head == NULL)
  {
    return;
  }
  professional* current = head;
  professional* next;

  while (current->next != NULL)
   {

     if ((strcmp(current->firstName,current->next->firstName) == 0) && (strcmp(current->lastName,current->next->lastName) == 0)&&current->phoneNumber==current->next->phoneNumber&&current->officeNumber==current->next->officeNumber)
     {
      delete_Professional_Contact(current->next,&current);
     }
     else
     {
        current = current->next;
      }

    }

}

statusCode insert_into_personal(personal** head)                                
{
  statusCode ret_val = SUCCESS;
  personal* nptr;
  nptr = (personal*) malloc(sizeof(personal));                              
  if(nptr!=NULL)
  {
  	printf("Enter the contact detials\n");
    printf("__________________________\n");                               
    printf("Enter the first name:");
    scanf("%s",nptr->firstName);
    printf("Enter the last name:");
    scanf("%s",nptr->lastName);
    printf("Enter phone number:");
    scanf("%lld",&nptr->phoneNumber);                                       

    nptr->next = (*head);
    nptr->prev = NULL;
    if(*head!=NULL)
    {
      (*head)->prev = nptr;
    }
    *head = nptr;
    
  }
  else
  {
	ret_val = FAILURE;
  }

    return ret_val;
}



void edit_Personal_Contact(personal* lptr)
{
  printf("The contact details \n");
  printf("_________________________\n");                                  
  printpersonal(lptr);
  printf("Enter the new details\n");
  printf("__________________________\n");
  printf("Enter the first name:");
  scanf("%s",lptr->firstName);
  printf("\nEnter the last name:");
  scanf("%s",lptr->lastName);
  printf("\nEnter phone number:");
  scanf("%lld",&lptr->phoneNumber);                                         

}

void delete_Personal_Contact(personal* lptr,personal** head)
{
  if(*head == lptr)
  {
    *head = lptr->next;
  }
  if(lptr->next!=NULL)
  {
    lptr->next->prev = lptr->prev;                                          
  }
  if(lptr->prev!=NULL)
  {
    lptr->prev->next = lptr->next;
  }
}

personal* search_by_personal_num(long long int number,personal* list_ptr)
{
  personal* lptr ;
  lptr = list_ptr;

  while(lptr!=NULL)
  {
    if(lptr->phoneNumber==number) return lptr;                              
    lptr=lptr->next;
  }

  return lptr;
}

void search_personal_con_by_name(char* firstName,char* lastName,personal* list_ptr)
{
  personal* lptr;
  statusCode sc = FAILURE;
  lptr = list_ptr;
  while(lptr!=NULL)
  {
    if(strcmp(lptr->firstName,firstName)==0 && strcmp(lptr->lastName,lastName)==0)
    {
      printf("_______________________\n");
      printpersonal(lptr);
      printf("________________________\n");
      sc = SUCCESS;                                                         
    }
    lptr= lptr->next;
  }

  if(sc == FAILURE)
  {
    printf("There is no contact with the name %s %s\n",firstName,lastName);
  }

}

void display_all_personal_cons(personal* list_ptr)
{
  personal* lptr;
  lptr = list_ptr;
  printf("!!!!!!!!!!!\n");
  printf("PERSONAL CONTACTS\n");
  printf("!!!!!!!!!!!!!\n");                                     
  while(lptr!=NULL)
  {
    printf("____________________\n");
    printpersonal(lptr);
    printf("_____________________\n");
    lptr = lptr->next;
  }

}

personal *split_Personal(personal *head)
{
    personal *first = head,*second = head;
    while (first->next && first->next->next)
    {
        first = first->next->next;
        second = second->next;
    }                                                                       
    personal *temp = second->next;
    second->next = NULL;
    return temp;
}

boolean comp_personal(personal*first,personal* second)
{
	if(strcmp(first->firstName,second->firstName)==0)
  	{
    if(strcmp(first->lastName,second->lastName)<0)
    {
      return TRUE;
    }
    else if(strcmp(first->lastName,second->lastName)==0)                    
    {
      if(first->phoneNumber<second->phoneNumber)
      {
        return TRUE;
      }
    }
   else if(strcmp(first->firstName,second->firstName)<0)
   {
    return TRUE;
   }
  
  }

  return FALSE;
}

personal *m_personal(personal *first, personal *second)//merge
{
	if (second==NULL)
    {
      return first;
    }
    if (first==NULL)
    {
      return second;
    }
	if (comp_personal(first,second))                                      
    {
        first->next = m_personal(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = m_personal(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

personal* sort_personal(personal* head)                                      
{
  if(head==NULL||head->next == NULL)
  {
    return head;
  }
  personal* temp = split_Personal(head);

  head = sort_personal(head);
  temp = sort_personal(temp);

  return m_personal(head,temp);

}

personal* cr_personal_list(int number)                                    
{
  personal* list_ptr=NULL;
  statusCode sc;
  int i;
  for(i=1; i<=number; i++)
  {
    sc = insert_into_personal(&list_ptr);
    if(sc==FAILURE)
    {
      return NULL;
    }
  }

  return list_ptr;

}


void push_Personal(personal** resultHead, personal* lptr)
{                                                                           
  personal* newNode= (personal*)malloc(sizeof(personal));
  strcpy(newNode->firstName ,lptr->firstName);
  strcpy(newNode->lastName,lptr->lastName);
  newNode->phoneNumber = lptr->phoneNumber;
  newNode->next = (*resultHead);
  (*resultHead) = newNode;
}

boolean PresentPersonal(personal* head, personal* ptr)
{
  personal* lptr = head;
  while(lptr!=NULL)
  {
    if(strcmp(lptr->firstName,ptr->firstName)==0 && strcmp(lptr->lastName, ptr->lastName)==0 && lptr->phoneNumber == ptr->phoneNumber)
    {
      return TRUE;
    }
    lptr= lptr->next;
  }

  return FALSE;
}

personal* U_Personal(personal* first, personal* second)  //union                
{

    personal* result = NULL;
    personal *ptr1 = first, *ptr2 = second;
	 while (ptr2 != NULL)
	  {
        if (!PresentPersonal(result, ptr2))
            push_Personal(&result, ptr2);
        ptr2 = ptr2->next;
    }
    while (ptr1 != NULL) 
	{
        push_Personal(&result, ptr1);
        ptr1 = ptr1->next;
    }
	return result;
}

void del_personal_duplicates(personal* head)
{
  if (head == NULL)
  {
    return;
  }
  personal* current = head;
  personal* next;

  while (current->next != NULL)
   {

     if ((strcmp(current->firstName,current->next->firstName) == 0) && (strcmp(current->lastName,current->next->lastName) == 0)&&current->phoneNumber==current->next->phoneNumber)
     {
      delete_Personal_Contact(current->next,&current);
     }
     else
     {
        current = current->next;
      }

    }

}



statusCode insert_Phonebook(phonebook** head,personal* personalHead,professional* professionalHead)
{

statusCode ret_val= SUCCESS;
phonebook* nptr = (phonebook*)malloc(sizeof(phonebook));
if(nptr==NULL)
{
  ret_val = FAILURE;
}
else
{
  printf("Enter the owner detials\n");
  printf("----------------------------\n");
  fflush(stdin);
  printf("Enter the name of owner:");
  fflush(stdin);
  fgets(nptr->ownerName,SIZE,stdin);
  printf("Enter email of owner:");
  fgets(nptr->email,SIZE,stdin);
  printf("Enter owner address");
  fgets(nptr->address,SIZE,stdin);
  nptr->personalHeader = personalHead;
  nptr->professionalHeader = professionalHead;
  printf("Enter total duration of calls\n");
  printf("No of hours:");
  scanf("%d",&nptr->hours);
  printf("No of minutes");
  scanf("%d",&nptr->minutes);
  nptr->next = (*head);
  nptr->prev = NULL;
  if(*head!=NULL)
  {
    (*head)->prev = nptr;
  }
  *head = nptr;
}

  return ret_val;
}

void printPhonebook(phonebook* lptr)
{

  printf("The owner name is %s\n",lptr->ownerName);
  printf("The owner email is %s\n",lptr->email);
  printf("The owner address is %s\n",lptr->address);
  printf("Total duration of calls is %d:%d\n",lptr->hours,lptr->minutes);
  display_all_personal_cons(lptr->personalHeader);
  displayProfessional(lptr->professionalHeader);

}

void displayAllPhonebook(phonebook* list_ptr)
{
  phonebook* lptr;
  lptr = list_ptr;
 	printf("DATABASE OF CONTACT LIST\n");
  while(lptr!=NULL)
  {
    
    printPhonebook(lptr);
    lptr = lptr->next;
  }
}

phonebook*splitPhonebook(phonebook*head)
{
    phonebook*first = head,*second = head;
    while (first->next && first->next->next)
    {
        first = first->next->next;
        second = second->next;
    }
    phonebook*temp = second->next;
    second->next = NULL;
    return temp;
}

boolean comp_Phonebook(phonebook*first,phonebook* second)
{
  if(first->hours > second->hours)
  {
    return TRUE;
  }
  else if(first->hours == second->hours)
  {
    if(first->minutes > second -> minutes)
    {
      return TRUE;
    }
  }

  return FALSE;
}

phonebook*mergePhonebook(phonebook*first, phonebook*second)
{

    if (first==NULL)
    {
      return second;
    }

    if (second==NULL)
    {
      return first;
    }

    if (comp_Phonebook(first,second))
    {
        first->next = mergePhonebook(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = mergePhonebook(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

phonebook* sortPhonebook(phonebook* head)
{
  if(head==NULL||head->next == NULL)
  {
    return head;
  }
  phonebook* temp = splitPhonebook(head);

  head = sortPhonebook(head);
  temp = sortPhonebook(temp);

  return mergePhonebook(head,temp);

}

void search_Phonebook(phonebook* list_ptr,char* name)
{
  phonebook* lptr;
  statusCode sc = FAILURE;
  lptr = list_ptr;
  while(lptr!=NULL)
  {
    if(strcmp(lptr->ownerName,name)==0)
    {
      printPhonebook(lptr);
      printf("________________\n");
      sc = SUCCESS;
    }
    lptr = lptr->next;
  }
  if(sc == FAILURE)
  {
    printf("sorry there is no owner with name %s\n",name );
  }
}


void main()
{

  int option;
  personal* personalHead=NULL;
  professional* professionalHead=NULL;
  phonebook* phonebookHead = NULL;
  statusCode status;
  char type[20];
  long long int number;
  while(TRUE)
  {
    printf("0.Exit.\n");
    printf("\n1.Add a new contact.");
    printf("\n2.Edit a contact :");
    printf("\n3.Delete a contact.:");
    printf("\n4.Search a contact.");
    printf("\n5.Display all contacts.");
    printf("\n6.sort contact list");
    printf("\n7.merge two contact lists");
    printf("\n8.remove duplicate contacts.");
    printf("\n9.add this phonebook to database.");
    printf("\n10.display database");
    printf("\n11.search database");
	printf("Enter your option :");
    scanf("%d",&option);
    switch (option)
    {

      case 0:
      {
        printf("Program Terminated\n");
        exit(0);
      }

      case 1:
      {

        printf("\nEnter the type of contact(personal/professional):");
        scanf("%s",type);
        if(strcmp(type,"personal")==0)
        {
          status = insert_into_personal(&personalHead);
          if(status==FAILURE)
          {
            printf("\nsorry contact creation failed");
            exit(0);
          }
          else
          {
            printf("\nThe personal contact is successfully created.\n");
            printf("----------------------------------------\n");
            printpersonal(personalHead);
          }

        }
        else
        {
          status = insert_professional(&professionalHead);
          if(status==FAILURE)
          {
            printf("sorry contact creation failed\n");
            exit(0);
          }
          else
          {
            printf("The professional contact is successfully created\n");
            printf("----------------------------------------\n");
            printprofessional(professionalHead);
          }
        }
        break;
      }

      case 2:
      {
        printf("Enter the contact to edit(personal/professional):");
        scanf("%s",type);
        printf("Enter the phone number of contact you want to edit:");
        scanf("%lld", &number);
        if(strcmp(type,"personal")==0)
        {
          personal* lptr;
          lptr=search_by_personal_num(number,personalHead);
          if(lptr==NULL)
          {
            printf("No contact with the number %lld\n",number);
          }
          else
          {
            edit_Personal_Contact(lptr);
            printf("modified details are\n");
            printpersonal(lptr);
          }

        }
        else
        {
          professional* lptr;
          lptr = search_Professional_Contact_by_number(number,professionalHead);
          if(lptr==NULL)
          {
            printf("No contact with the number %lld\n",number);
          }
          else
          {
            edit_Professional_Contact(lptr);
            printf("modified details are\n");
           
            printprofessional(lptr);
          }

        }

        break;
      }

      case 3:
      {

        printf("Enter the conatact type to delete(personal/professional):");
        scanf("%s",type);
        printf("Enter the contact number to delete:");
        scanf("%lld", &number);
        if(strcmp(type,"personal")==0)
        {
          personal* lptr;
          lptr=search_by_personal_num(number,personalHead);
          if(lptr==NULL)
          {
              printf("No contact with the number %lld\n",number);
          }
          else
          {
            delete_Personal_Contact(lptr,&personalHead);
            printf("The deleted contact details are\n");
            printpersonal(lptr);
            free(lptr);
          }

        }
        else
        {
          professional* lptr;
          lptr = search_Professional_Contact_by_number(number,professionalHead);
          if(lptr==NULL)
          {
              printf("No contact with the number %lld\n",number);
          }
          else
          {
            delete_Professional_Contact(lptr,&professionalHead);
            printf("deleted contact details are\n");
            printprofessional(lptr);
            free(lptr);
          }

        }

        break;
      }

      case 4:
      {
        printf("Enter the type of contact you want to search(personal/professional):");
        scanf("%s",type);
        printf("choose how u want to search\n");
		printf("1.search by name\n");
		printf("2.search by phone number.\n");
        printf("Enter your option:");
        scanf("%d",&option);
        if(option==1)
        {
          printf("Enter the first name:");
          char firstName[SIZE];
          scanf("%s",firstName);
          printf("Enter the second name:");
          char secondName[SIZE];
          scanf("%s",secondName);
          if(strcmp(type,"personal")==0)
          {
            search_personal_con_by_name(firstName,secondName,personalHead);
          }
          else
          {
            search_Professional_by_name(firstName,secondName,professionalHead);
          }

        }
        else
        {
          printf("Enter the number:");
          scanf("%lld",&number);
          if(strcmp(type,"personal")==0)
          {
            personal* lptr;
            lptr=search_by_personal_num(number,personalHead);
            if(lptr==NULL)
            {
                printf("No contact with the number %lld\n",number);
            }
            else
            {
              printpersonal(lptr);
            }

          }
          else
          {
            professional* lptr;
            lptr=search_Professional_Contact_by_number(number,professionalHead);
            if(lptr!=NULL)
            {
                printprofessional(lptr);
				
            }
            else
            {
             	printf("No contact with the number %lld\n",number); 
            }

          }

        }

        break;
      }

      case 5:
      {

        printf("Enter the contact list type  you want to display(personal/professional):");
        scanf("%s",type);
        if(strcmp(type,"personal")==0)
        {
          display_all_personal_cons(personalHead);
        }
        else
        {
          displayProfessional(professionalHead);
        }

        break;
      }

      case 6:
      {
        personal* personalHead1=NULL;
        professional* professionalHead1=NULL;
        int number;
        printf("Enter the list type  to sort(personal/professional):");
        scanf("%s",type);
        if(strcmp(type,"personal")==0)
        {
          printf("Enter the number of contacts:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
         
          personalHead1 = cr_personal_list(number);
          if(personalHead1==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            personalHead1 = sort_personal(personalHead1);
            printf("Sorted contact list is\n");
            display_all_personal_cons(personalHead1);
          }

        }
        else
        {
          printf("Enter the number of contacts:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
          printf("----------------------\n");
          professionalHead1 = cr_ProfessionalList(number);
          if(professionalHead1==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            professionalHead1 = s_Professional(professionalHead1);
            printf("Sorted contact list is\n");
            displayProfessional(professionalHead1);
          }

        }

        break;
      }

      case 7:
      {
        personal* personalHead1=NULL;
        personal* personalHead2=NULL;
        personal* personalResultHead = NULL;
        professional* professionalHead1=NULL;
        professional* professionalHead2=NULL;
        professional* professionalResultHead=NULL;
        int number;
        printf("Enter the list type to merge(personal/professional):");
        scanf("%s",type);
        if(strcmp(type,"personal")==0)
        {
          printf("Enter the number of contacts in list1:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
         
          personalHead1 = cr_personal_list(number);
          if(personalHead1==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            personalHead1 = sort_personal(personalHead1);
          }

          printf("Enter the number of contacts in list2:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
          personalHead2 = cr_personal_list(number);
          if(personalHead2==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            personalHead2 = sort_personal(personalHead2);
          }

          personalResultHead = U_Personal(personalHead1,personalHead2);
          printf("union of two linked lists is \n");
          personalResultHead = sort_personal(personalResultHead);
          display_all_personal_cons(personalResultHead);
        }
        else
        {
          printf("Enter the number of contacts in list1:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
          professionalHead1 = cr_ProfessionalList(number);
          if(professionalHead1==NULL)
          {
            printf("Can't create the required list\n");
          }
          else
          {
            professionalHead1 = s_Professional(professionalHead1);
          }

          printf("Enter the number of contacts in list2:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
          professionalHead2 = cr_ProfessionalList(number);
          if(professionalHead2==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            professionalHead2 = s_Professional(professionalHead2);
          }

          professionalResultHead = u_Professional(professionalHead1,professionalHead2);
          printf("union of two linked lists is \n");
          professionalResultHead = s_Professional(professionalResultHead);
          displayProfessional(professionalResultHead);
        }

        break;
      }

      case 8:
      {
        int number;
        personal* personalHead1=NULL;
        professional* professionalHead1=NULL;
        printf("Enter the list type to remove duplicates(personal/professional):");
        scanf("%s",type);
        if(strcmp(type,"personal")==0)
        {
          printf("Enter the number of contacts in list:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
         
          personalHead1 = cr_personal_list(number);
          printpersonal(personalHead1);
          if(personalHead1==NULL)
          {
            printf("can't create the required list\n");
          }
          else
          {
            personalHead1 = sort_personal(personalHead1);
          }

          del_personal_duplicates(personalHead1);
          printf("List after removing duplicates\n");
          display_all_personal_cons(personalHead1);
        }
        else
        {

          printf("Enter the number of contacts in list:");
          scanf("%d",&number);
          printf("Enter the contacts\n");
          printf("--------------------------\n");
          professionalHead1 = cr_ProfessionalList(number);
          if(professionalHead1==NULL)
          {
            printf("sorry can't create the required list\n");
          }
          else
          {
            professionalHead1=s_Professional(professionalHead1);
          }

          delete_ProfessionalDuplicates(professionalHead1);
          printf("List after removing duplicates\n");
          displayProfessional(professionalHead1);

        }

      }

      case 9:
      {

        status=insert_Phonebook(&phonebookHead,personalHead,professionalHead);
        if(status==FAILURE)
        {
          printf("cant add this phonebook to database\n");
        }
        printPhonebook(phonebookHead);
        break;
      }

      case 10:
      {
        displayAllPhonebook(phonebookHead);
        break;
      }

      case 11:
      {
        printf("Enter the name of owner:");
        char name[SIZE];
        fgets(name,SIZE,stdin);
        search_Phonebook(phonebookHead,name);
      }
    }

    personalHead = sort_personal(personalHead);
    professionalHead = s_Professional(professionalHead);
    phonebookHead = sortPhonebook(phonebookHead);
  }

}
BT20CSE085_.c
Displaying BT20CSE085_.c.
