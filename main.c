#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define LINE_LEN 256
#define clear system("clear||@cls");


typedef struct Device_type {
    char *name;
    struct Device_type *next;
    struct Device_type *prev;
}device_type;

typedef struct Gadgets{
    struct Device_type* device_type;
    char *name;
    int no;
    int battery_capacity;
    int quantity;
    float price;
    float screen_diag;
    int color_in_RGB[3];
    struct Gadgets *next;
    struct Gadgets *prev;
} gadget;



typedef struct dt_Head {
    struct Device_type *first;
    int count;
    struct Device_type *last;
} dt_head;

typedef struct g_Head{
    struct Gadgets* first;
    struct Gadgets* last;
    int count;
}g_head;

char** split(char* line, const char sep);
void output(g_head *hd, dt_head *types);
void fill(dt_head * dth, FILE* ffp);
dt_head * make_dt(FILE* ffp);
void input_from_scv(g_head *hd, dt_head * dev_type, char* _);
g_head *make_head();
char* bgets(char *st, int const len, FILE *fp);
void deletion(dt_head *dth, g_head *gh, int deletion);
char* get_name(gadget*item);
char* get_type(gadget*item);
int get_capacity(gadget*item);
int get_no(gadget*item);
int get_quantity(gadget*item);
float get_price(gadget *item);
float get_sd(gadget*item);
int get_R(gadget*item);
int get_G(gadget*item);
int get_B(gadget*item);
void swap_cpy_(gadget * temp0, gadget * temp1);
void swap_(gadget * temp0, gadget * temp1);
void sort_by_str(gadget * left, gadget * right, char* (*field)(gadget*));
void sort_by_int_(gadget * left, gadget * right, int (*field)(gadget*));
void sort_by_float_(gadget * left, gadget * right, float (*field)(gadget*));
void filter_by_str_(g_head*hd,dt_head *types,char* (*field)(gadget*));
void filter_by_int_(g_head*hd,dt_head *types,int (*field)(gadget*));
void filter_by_float_(g_head*hd,dt_head *types,float (*field)(gadget*));
void input_kb(g_head *hd,dt_head * dev_type);
device_type * search_or_fill(dt_head* hdt, char*dtName);
void edit(g_head*hd, dt_head*hdt,int id);
int gui();
void info();
void save_and_exit(g_head*hd, dt_head*dth, FILE*fp);


int main(){
    g_head *hd;
    dt_head *hdt;
    FILE * fp, *ffp, *fp1;
    char* line, yn,*line_;
    int ans,id,by, int_val;
    line = malloc(LINE_LEN);

    if(line == NULL) {printf("Memory Error.\n"); exit(1);}

    puts("Please maximize your window and press enter.");
    getchar();
    clear
    fp = fopen("lab07.txt", "r");
    if (fp == NULL) {printf("\nError Occurred While Trying To read the file. \nMaybe that file does not exist?\n");exit(1);}
    ffp = fopen("dev_type.txt", "r");
    if (ffp == NULL) {printf("\nError Occurred While Trying To read the file. \nMaybe that file does not exist?\n");exit(1);}
    hd = make_head();
    hdt = make_dt(ffp);
    fill(hdt, ffp);

    while(bgets(line, LINE_LEN, fp)) {
        input_from_scv(hd, hdt, line);
    }
    while(ans!=7){
        ans = gui();
        if (ans==0){
            info();
        }
        if (ans==1){
            printf("write data with , separator->");
            input_kb(hd,hdt);
        }
        if (ans==2) {
            printf("write id of node you want to edit->");
            scanf("%i",&id);
            printf("write new data with , separator->");
            edit(hd,hdt,id);
        }
        if (ans==3) {

            printf("write id of node you want to delete->");
            scanf("%i", &id);
            deletion(hdt, hd, id);
        }
        if(ans==4) {
            output(hd, hdt);
        }
        if (ans==5){
            printf("Fields:\n"
                   "1 - ID\n"
                   "2 - Quantity\n"
                   "3 - Name\n"
                   "4 - Device Type\n"
                   "5 - Capacity\n"
                   "6 - Screen\n"
                   "7 - Price\n"
                   "8 - R Color\n"
                   "9 - G Color\n"
                   "10 - B Color\n");
            printf("select field you want to search by->");
            scanf("%i",&by);
            if (by==1) {
                printf("ID->");
                scanf("%i", &int_val);
                filter_by_int_(hd, hdt, get_no);
            }
            if(by==2) {
                printf("Quantity->");
                scanf("%i", &int_val);
                filter_by_int_(hd, hdt, get_quantity);
            }
            if (by==3) {
                printf("Enter Name ->");
                filter_by_str_(hd, hdt, get_name);
            }
            if (by==4){
                printf("Enter Device Type ->");
                filter_by_str_(hd,hdt,get_type);
            }
            if(by==5){
                printf("Enter Capacity->");
                filter_by_int_(hd,hdt,get_capacity);
            }
            if(by==6){
                printf("Enter Screen Diagonal->");
                filter_by_float_(hd,hdt,get_sd);
            }
            if(by==7){
                printf("Enter Price->");
                filter_by_float_(hd,hdt,get_price);
            }
            if (by==8){
                printf("Enter Red Color Value->");
                filter_by_int_(hd,hdt,get_R);
            }
            if (by==9){
                printf("Enter Green Color Value->");
                filter_by_int_(hd,hdt,get_G);
            }
            if (by==10){
                printf("Enter Blue Color Value->");
                filter_by_int_(hd,hdt,get_B);
            }
        }
        if (ans==6){
            printf("Fields:\n"
                   "1 - ID\n"
                   "2 - Quantity\n"
                   "3 - Name\n"
                   "4 - Device Type\n"
                   "5 - Capacity\n"
                   "6 - Screen\n"
                   "7 - Price\n"
                   "8 - R Color\n"
                   "9 - G Color\n"
                   "10 - B Color\n");
            printf("select field you want to sort by->");
            scanf("%i",&by);
            if (by==1) {
                sort_by_int_(hd->first,hd->last,get_no);
            }
            if(by==2) {
                sort_by_int_(hd->first,hd->last,get_quantity);
            }
            if (by==3) {
                sort_by_str(hd->first,hd->last,get_name);
            }
            if (by==4){
                sort_by_str(hd->first,hd->last,get_type);
            }
            if(by==5){
                sort_by_int_(hd->first,hd->last,get_capacity);
            }
            if(by==6){
                sort_by_float_(hd->first,hd->last,get_sd);
            }
            if(by==7){
                sort_by_float_(hd->first,hd->last,get_price);
            }
            if (by==8){
                sort_by_int_(hd->first,hd->last,get_R);
            }
            if (by==9){
                sort_by_int_(hd->first,hd->last,get_G);
            }
            if (by==10){
                sort_by_int_(hd->first,hd->last,get_B);
            }
        }
    }
    if (ans==7){
        fp1 = fopen("lab07.txt","w");
        save_and_exit(hd,hdt,fp1);
    }
    fclose(fp);
    fclose(ffp);
    free(hd);
    free(hdt);
    return 0;
}

char** split(char* line, const char sep) {
    int separators_in_line, i, j, k, m;
    char** result_array = NULL;

    for (i = 0, separators_in_line = 0; i < strlen(line); i++)
        if(line[i] == sep) separators_in_line++;

    result_array = (char**)malloc((separators_in_line + 1) * sizeof (char*));
    if(result_array == NULL) return NULL;

    for(i = 0; i <= separators_in_line; i++) {
        result_array[i]=(char*)malloc(strlen(line)*sizeof(char));
        if(result_array[i]==NULL) return NULL;
    }

    k = m = 0;
    for(j=0;j<strlen(line);j++)
    {
        if(line[j]!=sep) result_array[m][j-k]=line[j];
        else
        {
            result_array[m][j-k]='\0';
            k=j+1;
            m++;
        }
    }
    return result_array;
}




//iphone 13,phone,5000,13,89990.99,6.0,255,255,134

void fill(dt_head * dth, FILE* ffp) {
    char* _;
    device_type * node;
    dth->first = NULL;
    dth->last =  NULL;
    dth->count = 0;
    _ = malloc(256);
    while(bgets(_, 256, ffp) != NULL) {
        node = (device_type *)malloc(sizeof(device_type));
        node->name = _;
        node->next=NULL;
        if(dth->count == 0) {
            dth->first = node;
            dth->last = node;
        }
        else {
            (dth->last)->next = node;
            node->prev = dth->last;
            dth->last = node;
        }
        dth->count++;
        _ = malloc(256);
    }
    rewind(ffp);
}

dt_head * make_dt(FILE* ffp) {
    dt_head * res;
    char* _;
    int lines;
    _ = malloc(256);
    lines = 0;
    while(bgets(_, 256, ffp) != NULL) {
        lines++;
    }
    res = (dt_head *)malloc(lines*sizeof(dt_head));
    rewind(ffp);
    return res;
}

void input_from_scv(g_head *hd, dt_head * dev_type, char* _) {
    int j;
    short int flag;
    gadget *db, *temp;
    device_type * fcn;
    char **splitLine, *facName;
    db = (gadget *)malloc(sizeof(gadget));

    splitLine = split(_, ',');
    if(splitLine == NULL) {
        printf("Memory Error.");
        exit(1);
    }

    db->name = splitLine[0];
    facName = splitLine[1];
    flag = 0;
    for(fcn = dev_type->first; fcn != NULL && !flag; fcn = fcn->next) {
        if(!strcmp(fcn->name, facName)) {
            db->device_type = fcn;
            flag = 1;
        }
    }
    if(db->device_type == NULL) {
        printf("Device %s not found in the list of device types.\nAre you sure you have necessary files?\n", facName);
        exit(1);
    }
    db->battery_capacity = (int)strtol(splitLine[2], NULL, 10);
    db->quantity = (int)strtol(splitLine[3], NULL, 10);
    db->price = (float)atof(splitLine[4]);
    db->screen_diag = (float)atof(splitLine[5]);
    for(j = 0; j < 3; j++) db->color_in_RGB[j] = (int)strtol(splitLine[6+j], NULL, 10);
    db->next = NULL;
    db->no = hd->count + 1;

    if(!hd->count) {
        hd->first = db;
        db->prev = NULL;
    }
    else {
        temp = hd->first;
        while(temp->next != NULL) temp = temp->next;
        temp->next = db;
        db->prev = temp;
    }

    hd->count++;
    hd->last = db;
    free(splitLine);
}

g_head *make_head() {
    g_head *ph=NULL;
    ph=(g_head*)malloc(sizeof(g_head));
    if(ph != NULL) ph->count=0;
    return ph;
}

void output(g_head *hd, dt_head *types){
    device_type *fak;
    gadget *temp;
    printf("Devices: ");
    for(fak = types->first; fak != NULL; fak = fak->next) {
        printf("%s ", fak->name);
    }
    printf("\nOutput:\n");
    temp = hd->first;
    printf("+-No-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
        temp = temp->next;
    }
    printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
           temp->no, temp->name,
           temp->device_type->name, temp->battery_capacity,
           temp->quantity,
           temp->screen_diag, temp->price,
           temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);

}

char* bgets(char *st, int const len, FILE *fp) {
    unsigned long str_len;
    char* err;
    err = fgets(st, len, fp);
    str_len = strlen(st);
    if (st[str_len - 1] == '\n') {
        if (st[str_len - 2] == '\r')
            st[str_len - 2] = '\0';
        else
            st[str_len - 1] = '\0';
    }
    return err;
}


void deletion(dt_head *dth, g_head *gh, int deleting){

    gadget * q;
    for(q = gh->first; q != NULL; q = q->next) {
        if(q->no == deleting) {
            if(q->next == NULL) {
                q->prev->next = NULL;
            } else if (q->prev == NULL) {
                gh->first = q->next;
                q->next->prev = NULL;
            } else {
                q->prev->next = q->next;
                q->next->prev = q->prev;
            }
        }
    }
    dth->last = dth->last->prev;
    dth->last->next = NULL;
}


int get_R(gadget*item){
    return item->color_in_RGB[0];
}

int get_G(gadget*item){
    return item->color_in_RGB[1];
}

int get_B(gadget*item){
    return item->color_in_RGB[2];
}

char* get_name(gadget*item){
    return item->name;
}

char* get_type(gadget*item){
    return item->device_type->name;
}

int get_capacity(gadget*item){
    return item->battery_capacity;
}

int get_no(gadget*item){
    return item->no;
}

int get_quantity(gadget*item){
    return item->quantity;
}

float get_price(gadget *item){
    return item->price;
}

float get_sd(gadget*item){
    return item->screen_diag;
}

void sort_by_str(gadget * left, gadget * right, char* (*field)(gadget*)) {
    gadget * last, * current;
    if (left != right) {
        if (left->next == right) {
            if((strcmp(field(left), field(right)) > 0 ))
                swap_(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if(strcmp(field(current), field(left)) < 0) {
                    last = last->next;
                    swap_(last, current);
                }
            } while (current != right);
            swap_(left, last);
            sort_by_str(left, last,field);
            if (last != right)
                sort_by_str(last->next, right,field);
        }
    }
}

void sort_by_int_(gadget * left, gadget * right, int (*field)(gadget*)) {
    gadget * last, * current;
    if (left != right) {
        if (left->next == right) {
            if(field(left)>field(right))
                swap_(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if(field(current)<field(left)) {
                    last = last->next;
                    swap_(last, current);
                }
            } while (current != right);
            swap_(left, last);
            sort_by_int_(left, last,field);
            if (last != right)
                sort_by_int_(last->next, right,field);
        }
    }
}

void sort_by_float_(gadget * left, gadget * right, float (*field)(gadget*)) {
    gadget * last, * current;
    if (left != right) {
        if (left->next == right) {
            if(field(left)>field(right))
                swap_(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if(field(current)<field(left)) {
                    last = last->next;
                    swap_(last, current);
                }
            } while (current != right);
            swap_(left, last);
            sort_by_float_(left, last,field);
            if (last != right)
                sort_by_float_(last->next, right,field);
        }
    }
}

void swap_(gadget * temp0, gadget * temp1) {
    gadget * buff;
    buff = (gadget *)malloc(sizeof(gadget));
    if(buff == NULL) {
        printf("fatal error: Unable to Allocate Memory (swap_: buff)\n\n");
        exit(1);
    }
    swap_cpy_(buff, temp1);
    swap_cpy_(temp1, temp0);
    swap_cpy_(temp0, buff);

    free(buff);
}

void swap_cpy_(gadget * temp0, gadget * temp1) {
    int i;
    temp0->no=temp1->no;
    for (i=0;i<3;i++){
        temp0->color_in_RGB[i]=temp1->color_in_RGB[i];
    }
    temp0->device_type = temp1->device_type;
    temp0->name=temp1->name;
    temp0->screen_diag=temp1->screen_diag;
    temp0->price=temp1->price;
    temp0->battery_capacity=temp1->battery_capacity;
    temp0->quantity = temp1->quantity;
}

void filter_by_str_(g_head*hd,dt_head *types,char* (*field)(gadget*)){
    char string[100];
    device_type *fak;
    gadget *temp;
    getchar();
    bgets(string,LINE_LEN,stdin);
    printf("Devices: ");
    for(fak = types->first; fak != NULL; fak = fak->next) {
        printf("%s ", fak->name);
    }
    printf("\nOutput:\n");
    temp = hd->first;
    printf("+-No-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        if ((strcmp(field(temp),string))==0){
            printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
                   temp->no, temp->name,
                   temp->device_type->name, temp->battery_capacity,
                   temp->quantity,
                   temp->screen_diag, temp->price,
                   temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
        }
        temp = temp->next;
    }

    if (strcmp(field(temp),string)==0) {
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
    }
}

void filter_by_int_(g_head*hd,dt_head *types,int (*field)(gadget*)){
    device_type *fak;
    gadget *temp;
    int equals;
    scanf("%i",&equals);
    printf("Devices: ");
    for(fak = types->first; fak != NULL; fak = fak->next) {
        printf("%s ", fak->name);
    }
    printf("\nOutput:\n");
    temp = hd->first;
    printf("+-No-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        if (field(temp)==equals){
            printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
                   temp->no, temp->name,
                   temp->device_type->name, temp->battery_capacity,
                   temp->quantity,
                   temp->screen_diag, temp->price,
                   temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
        }
        temp = temp->next;
    }

    if (field(temp)==equals) {
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
    }
}



void filter_by_float_(g_head*hd,dt_head *types,float (*field)(gadget*)){
    device_type *fak;
    gadget *temp;
    float equals;
    scanf("%f",&equals);
    printf("Devices: ");
    for(fak = types->first; fak != NULL; fak = fak->next) {
        printf("%s ", fak->name);
    }
    printf("\nOutput:\n");
    temp = hd->first;
    printf("+-No-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        if (field(temp)==equals){
            printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
                   temp->no, temp->name,
                   temp->device_type->name, temp->battery_capacity,
                   temp->quantity,
                   temp->screen_diag, temp->price,
                   temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
            }
        temp = temp->next;
    }

    if (field(temp)==equals) {
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
    }
}


void input_kb(g_head *hd,dt_head * dev_type){
    char line[100],**pLine;
    gadget *Node;
    Node = malloc(sizeof(gadget));
    getchar();
    bgets(line,100,stdin);
    pLine= split(line,',');
    Node->name = pLine[0];
    Node->device_type = search_or_fill(dev_type,pLine[1]);
    Node->battery_capacity=(int)strtol(pLine[2],NULL,10);
    Node->quantity=(int)strtol(pLine[3],NULL,10);
    Node->price=(float) atof(pLine[4]);
    Node->screen_diag=(float) atof(pLine[5]);
    Node->color_in_RGB[0]=(int)strtol(pLine[6],NULL,10);
    Node->color_in_RGB[1]=(int)strtol(pLine[7],NULL,10);
    Node->color_in_RGB[2]=(int)strtol(pLine[8],NULL,10);
    free(pLine);
    hd->last->next=Node;
    hd->first->prev=Node;
    Node->next=NULL;
    Node->prev=hd->last;
    hd->last=Node;
    hd->count++;
    Node->no=hd->count;
}

void edit(g_head*hd, dt_head*hdt,int id){
    char line[100],**pLine;
    gadget *temp;
    temp = malloc(sizeof(gadget));
    getchar();
    bgets(line,100,stdin);
    pLine= split(line,',');
    temp = hd->first;
    while (temp->next!=NULL){
        if(temp->no==id){
            temp->name = pLine[0];
            temp->device_type = search_or_fill(hdt,pLine[1]);
            temp->battery_capacity=(int)strtol(pLine[2],NULL,10);
            temp->quantity=(int)strtol(pLine[3],NULL,10);
            temp->price=(float) atof(pLine[4]);
            temp->screen_diag=(float) atof(pLine[5]);
            temp->color_in_RGB[0]=(int)strtol(pLine[6],NULL,10);
            temp->color_in_RGB[1]=(int)strtol(pLine[7],NULL,10);
            temp->color_in_RGB[2]=(int)strtol(pLine[8],NULL,10);
            free(pLine);
        }
        temp=temp->next;
    }
}

device_type * search_or_fill(dt_head* hdt, char*dtName){
    device_type *dt;
    int flag;
    flag=0;
    for(dt = hdt->first; dt != NULL && flag!=1; dt = dt->next) {
        if(strcmp(dt->name, dtName) == 0) {
            flag = 1;
        }
    }
    if (flag==1){
        dt = dt->prev;
    }
    if (flag==0){
        dt = (device_type *)malloc(sizeof(device_type));
        dt->name = dtName;
        dt->next=NULL;
        (hdt->last)->next = dt;
        dt->prev = hdt->last;
        hdt->last = dt;
        hdt->count++;
    }
    return dt;
}

int gui(){
    int cmd;
    printf("0 - Info\n"
           "1 - Add new node\n"
           "2 - Edit node by id\n"
           "3 - Delete node by id\n"
           "4 - Output\n"
           "5 - Search by field\n"
           "6 - Sort by field\n"
           "7 - Save & Exit\n");
    scanf("%i", &cmd);
    return cmd;
}

void info(){
    printf("Hello! This is my project as course work for programming subject.\n"
           "The program is an electronic card file on the subject area gadgets. \n"
           "The program works with source .txt files, loading information from there into structures.\n"
           "The card file is a table with data about gadgets, which has fields:\n"
           "ID\n"
           "Name\n"
           "Device type (getting from a linked list of device types)\n"
           "Battery capacity\n"
           "Quantity\n"
           "Price\n"
           "Screen diagonal\n"
           "Color in RGB format\n"
           "All fields must be separated by a comma(',').\n"
           "You can manage the file cabinet using an interface that offers the following operations:\n"
           "0 - Info (You are here now).\n"
           "1 - Add new node - You can add new node in list of gadgets.\n"
           "2 - Edit node by ID - You can write data with which you want to replace the original element by specifying its ID.\n"
           "3 - Delete node by id - You can delete node from list of gadgets by ID.\n"
           "4 - Output - You can see changes you made with data.\n"
           "5 - Search by field - You can filter output with chosen value in chosen field.\n"
           "6 - Sort by field - You can sort data by chosen field.\n"
           "7 - Save & Exit - You can save changes you made in source .txt file.\n"
           "Good luck and enjoy!\n");
}

void save_and_exit(g_head *hd, dt_head*dth, FILE *fp){
    gadget *temp;
    if(fp==NULL){
        printf("error");
    }
    temp = hd->first;
    while (temp->next!=NULL){
        fprintf(fp,"%s,%s,%i,%i,%f,%f,%i,%i,%i\n",
                temp->name,temp->device_type->name,temp->battery_capacity,temp->quantity,
                temp->price,temp->screen_diag,temp->color_in_RGB[0],temp->color_in_RGB[1],temp->color_in_RGB[2]);
        temp = temp->next;
    }
    fprintf(fp,"%s,%s,%i,%i,%f,%f,%i,%i,%i\n",
            temp->name,temp->device_type->name,temp->battery_capacity,temp->quantity,
            temp->price,temp->screen_diag,temp->color_in_RGB[0],temp->color_in_RGB[1],temp->color_in_RGB[2]);

}