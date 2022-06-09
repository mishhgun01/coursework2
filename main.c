#include <stdio.h>
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


int q(char* str);
void output_dt(dt_head*dt);
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
void sort_by_str(gadget * left, gadget * right, char* (*field)(gadget*), int des);
void sort_by_int_(gadget * left, gadget * right, int (*field)(gadget*), int asc);
void sort_by_float_(gadget * left, gadget * right, float (*field)(gadget*), int asc);
int filter_by_str_(g_head*hd,char* (*field)(gadget*));
int filter_by_int_(g_head*hd,int (*field)(gadget*));
int filter_by_float_(g_head*hd,float (*field)(gadget*));
void input_kb(g_head *hd,dt_head * dev_type, int dt);
device_type * search_or_fill(dt_head* hdt, char*dtName);
void edit(g_head*hd, dt_head*hdt,int id,int dt);
int gui();
void info();
void save_and_exit(g_head*hd, FILE*fp);


int main(){
    g_head *hd;
    dt_head *hdt;
    FILE * fp, *ffp, *fp1;
    char* line,*_line;
    int ans,id,by, int_val, reverse, found;
    line = malloc(LINE_LEN);

    if(line == NULL) {printf("Memory Error.\n"); exit(1);}
    _line = malloc(LINE_LEN);

    if(_line == NULL) {printf("Memory Error.\n"); exit(1);}

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
    while(ans!=7) {
        ans = gui();
        switch (ans) {
            case 0:
                clear
                info();
                break;
            case 1:
                clear
                printf("Select number of Device Type:\n");
                output_dt(hdt);
                int_val = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)){
                    puts("It's not a number...Try again from main menu.");
                    break;
                }
                printf("EXAMPLE: name, battery capacity, quantity, price, screen diagonal, R color, G color, B color\n");
                printf("write data with , separator AS EXAMPLE->");
                input_kb(hd, hdt, int_val);
                break;
            case 2:
                clear
                output(hd, hdt);
                printf("write id of node you want to edit->");
                id = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)){
                    puts("It's not a number...Try again from main menu.");
                    break;
                }

                if (id > hd->count||id<1){
                    puts("No Records with this ID.\n");
                    break;
                }
                printf("Select number of Device Type:\n");
                output_dt(hdt);
                int_val = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)){
                    puts("It's not a number...Try again from main menu.");
                    break;
                }
                if (int_val>4||int_val<1){
                    puts("No Device Type with this number.\n");
                    break;
                }
                printf("EXAMPLE: name, battery capacity, quantity, price, screen diagonal, R color, G color, B color\n");
                printf("write data with , separator AS EXAMPLE->");
                edit(hd, hdt, id,int_val);
                break;
            case 3:
                clear
                output(hd, hdt);
                printf("write id of node you want to delete->");

                id = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)){
                    puts("It's not a number...Try again from main menu.");
                    break;
                }
                if (id > hd->count||id<1){
                    puts("No Records with this ID.\n");
                    break;
                }
                deletion(hdt, hd, id);
                break;
            case 4:
                clear
                output(hd, hdt);
                break;
            case 5:
                clear
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

                by = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)||by>10||by<1){
                    puts("Wrong number or not a number at all...Try again from main menu.");
                    break;
                }
                switch (by) {
                    case 1:
                        printf("ID->");

                        int_val = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                        if(!isdigit(*line)){
                            puts("It's not a number...Try again from main menu.");
                            break;
                        }
                        if (id > hd->count||id<1){
                            puts("No Records with this ID.\n");
                            break;
                        }
                        found=filter_by_int_(hd, get_no);
                        if (found==0){
                            puts("Nothing found.\n");
                        }
                        break;
                    case 2:
                        printf("Quantity->");

                        int_val = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                        if(!isdigit(*line)){
                            puts("Wrong number...Try again from main menu.");
                            break;
                        }
                        found= filter_by_int_(hd,get_quantity);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 3:
                        printf("Enter Name ->");
                        found = filter_by_str_(hd,get_name);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 4:
                        output_dt(hdt);
                        printf("Enter Name Of Device Type ->");
                        found = filter_by_str_(hd, get_type);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 5:
                        printf("Enter Capacity->");
                        found = filter_by_int_(hd, get_capacity);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 6:
                        printf("Enter Screen Diagonal->");
                        found = filter_by_float_(hd, get_sd);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 7:
                        printf("Enter Price->");
                        found = filter_by_float_(hd, get_price);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 8:
                        printf("Enter Red Color Value->");
                        found=filter_by_int_(hd, get_R);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 9:
                        printf("Enter Green Color Value->");
                        found = filter_by_int_(hd, get_G);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                    case 10:
                        printf("Enter Blue Color Value->");
                        found = filter_by_int_(hd, get_B);
                        if (found==0){
                            puts("Nothing found.\n");
                            break;
                        }
                        break;
                }
                break;
            case 6:
                clear
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
                printf("select field you want to sort by->\n");
                by = (int)strtol(fgets(line, 10, stdin), NULL, 10);
                if(!isdigit(*line)||by>10||by<1){
                    puts("It's not a number from list...Try again from main menu.");
                    break;
                }
                printf("1 - in ascending \nOR\n2 - in descending order\n->");
                int_val = (int) strtol(fgets(_line,10,stdin),NULL,10);
                if(!isdigit(*_line)||(int_val!=1&&int_val!=2)){
                    puts("Wrong number from list...Try again from main menu.");
                    break;
                }
                switch (by) {
                    case 1:
                        sort_by_int_(hd->first, hd->last, get_no, int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 2:
                        sort_by_int_(hd->first, hd->last, get_quantity,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 3:
                        sort_by_str(hd->first, hd->last, get_name, int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 4:
                        sort_by_str(hd->first, hd->last, get_type, int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 5:
                        sort_by_int_(hd->first, hd->last, get_capacity,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 6:
                        sort_by_float_(hd->first, hd->last, get_sd,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 7:
                        sort_by_float_(hd->first, hd->last, get_price,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 8:
                        sort_by_int_(hd->first, hd->last, get_R,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 9:
                        sort_by_int_(hd->first, hd->last, get_G,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                    case 10:
                        sort_by_int_(hd->first, hd->last, get_B,int_val);
                        puts("Success! You can see changes in Output.\n");
                        break;
                }
                case 7:
                    break;
        }
    }
    if (ans==7){
        clear
        fp1 = fopen("save.txt","w");
        save_and_exit(hd,fp1);
    }
    fclose(fp);
    fclose(ffp);
    free(hd);
    free(hdt);
    printf("See You!\n");
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




//iphone 13,5000,13,89990.99,6.0,255,255,134

void fill(dt_head * dth, FILE* ffp) {
    char* _;
    device_type * node;
    dth->first = NULL;
    dth->last =  NULL;
    dth->count = 0;
    _ = malloc(256);
    while(bgets(_, 256, ffp) != NULL) {
        node = (device_type *)malloc(sizeof(device_type));
        if (node!=NULL){
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
    if (res!=NULL){
        rewind(ffp);
        return res;
    }
}

void input_from_scv(g_head *hd, dt_head * dev_type, char* _) {
    int j;
    short int flag;
    gadget *db, *temp;
    device_type * fcn;
    char **splitLine, *facName;
    db = (gadget *)malloc(sizeof(gadget));
    if(db!=NULL){
        splitLine = split(_, ',');
        if(splitLine!=NULL){
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
    }else{
        puts("Something went wrong. Try again later.\n");
    }

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
    printf("+-ID-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
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
    int deleted;
    for(q = gh->first; q != NULL; q = q->next) {
        if(q->no == deleting) {
            if(q->next == NULL) {
                q->prev->next = NULL;
                deleted =1;
            } else if (q->prev == NULL) {
                gh->first = q->next;
                q->next->prev = NULL;
                deleted =1;
            } else {
                q->prev->next = q->next;
                q->next->prev = q->prev;
                deleted =1;
            }
        }
    }
    if (deleted==1){
        puts("Success! You can see changes in Output.\n");
    }else{
        puts("Something went wrong...Try again from main menu.\n");
    }
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

void sort_by_str(gadget * left, gadget * right, char* (*field)(gadget*), int asc) {
    gadget *last, *current;
    if (asc == 1) {

        if (left != right) {
            if (left->next == right) {
                if ((strcmp(field(left), field(right)) > 0))
                    swap_(left, right);
            } else {
                last = left;
                current = left;
                do {
                    current = current->next;
                    if (strcmp(field(current), field(left)) < 0) {
                        last = last->next;
                        swap_(last, current);
                    }
                } while (current != right);
                swap_(left, last);
                sort_by_str(left, last, field, asc);
                if (last != right)
                    sort_by_str(last->next, right, field, asc);
            }
        }
    } else {

        if (left != right) {
            if (left->next == right) {
                if ((strcmp(field(left), field(right)) < 0))
                    swap_(left, right);
            } else {
                last = left;
                current = left;
                do {
                    current = current->next;
                    if (strcmp(field(current), field(left)) > 0) {
                        last = last->next;
                        swap_(last, current);
                    }
                } while (current != right);
                swap_(left, last);
                sort_by_str(left, last, field, asc);
                if (last != right)
                    sort_by_str(last->next, right, field, asc);
            }
        }
    }
}

void sort_by_int_(gadget * left, gadget * right, int (*field)(gadget*), int asc) {
    gadget * last, * current;
    if (asc ==1){
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
                sort_by_int_(left, last,field,asc);
                if (last != right)
                    sort_by_int_(last->next, right,field,asc);
            }
        }
    } else{
        if (left != right) {
            if (left->next == right) {
                if(field(left)<field(right))
                    swap_(left, right);
            } else {
                last = left;
                current = left;
                do {
                    current = current->next;
                    if(field(current)>field(left)) {
                        last = last->next;
                        swap_(last, current);
                    }
                } while (current != right);
                swap_(left, last);
                sort_by_int_(left, last,field,asc);
                if (last != right)
                    sort_by_int_(last->next, right,field,asc);
            }
        }
    }

}

void sort_by_float_(gadget * left, gadget * right, float (*field)(gadget*), int asc) {
    gadget * last, * current;
    if (asc==1){
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
                sort_by_float_(left, last,field,asc);
                if (last != right)
                    sort_by_float_(last->next, right,field,asc);
            }
        }
    }else{
        if (left != right) {
            if (left->next == right) {
                if(field(left)<field(right))
                    swap_(left, right);
            } else {
                last = left;
                current = left;
                do {
                    current = current->next;
                    if(field(current)>field(left)) {
                        last = last->next;
                        swap_(last, current);
                    }
                } while (current != right);
                swap_(left, last);
                sort_by_float_(left, last,field,asc);
                if (last != right)
                    sort_by_float_(last->next, right,field,asc);
            }
        }
    }
}

void swap_(gadget * temp0, gadget * temp1) {
    gadget * buff;
    buff = (gadget *)malloc(sizeof(gadget));
    if(buff != NULL) {
        swap_cpy_(buff, temp1);
        swap_cpy_(temp1, temp0);
        swap_cpy_(temp0, buff);
        free(buff);
    }
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

int filter_by_str_(g_head*hd,char* (*field)(gadget*)){
    char string[100];
    int type,found;
    gadget *temp;
    type = (int)strtol(fgets(string, 10, stdin), NULL, 10);
    if(!isdigit(*string)){
        puts("Wrong number...Try again from main menu.");
    }else{
        switch (type) {
            case 1:
                strcpy(string,"phone");
                break;
            case 2:
                strcpy(string, "laptop");
                break;
            case 3:
                strcpy(string,"tablet");
                break;
            case 4:
                strcpy(string,"computer");
                break;
        }
        printf("\nOutput:\n");
        temp = hd->first;
        found=0;
        printf("+-ID-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
        while(temp->next != NULL) {
            if (strstr(field(temp),string)!=NULL){
                found=1;
                printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
                       temp->no, temp->name,
                       temp->device_type->name, temp->battery_capacity,
                       temp->quantity,
                       temp->screen_diag, temp->price,
                       temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
            }
            temp = temp->next;
        }

        if (strstr(field(temp),string)!=NULL) {
            found=1;
            printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
                   temp->no, temp->name,
                   temp->device_type->name, temp->battery_capacity,
                   temp->quantity,
                   temp->screen_diag, temp->price,
                   temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
        }
    }
    return found;
}

int filter_by_int_(g_head*hd,int (*field)(gadget*)){
    gadget *temp;
    int equals, found;
    scanf("%i",&equals);
    printf("\nOutput:\n");
    temp = hd->first;
    found=0;
    printf("+-ID-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        if (field(temp)==equals){
            found=1;
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
        found=1;
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
    }
    return found;
}



int filter_by_float_(g_head*hd,float (*field)(gadget*)){
    gadget *temp;
    float equals;
    int found;
    scanf("%f",&equals);
    printf("\nOutput:\n");
    temp = hd->first;
    found=0;
    printf("+-ID-+-----------Name----------+--Device Type--+-Capacity-+-Quantity-+---Screen---+----Price---+----RGB Color----+\n");
    while(temp->next != NULL) {
        if (field(temp)==equals){
            found = 1;
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
        found=1;
        printf("| %-2d | %-23s | %-13s | %-8d | %-8d | %10.2f | %10.2f | %-3d | %-3d | %-3d |\n",
               temp->no, temp->name,
               temp->device_type->name, temp->battery_capacity,
               temp->quantity,
               temp->screen_diag, temp->price,
               temp->color_in_RGB[0], temp->color_in_RGB[1], temp->color_in_RGB[2]);
    }
    return found;
}


void input_kb(g_head *hd,dt_head * dev_type, int dt){
    char line[100],**pLine, dt_[15];
    gadget *Node;
    Node = malloc(sizeof(gadget));
    getchar();
    bgets(line,100,stdin);
    pLine= split(line,',');
    if(pLine!=NULL&&q(line)==7){
        switch (dt) {
            case 1:
                strcpy(dt_,"phone");
                break;
            case 2:
                strcpy(dt_, "laptop");
                break;
            case 3:
                strcpy(dt_,"tablet");
                break;
            case 4:
                strcpy(dt_,"computer");
                break;
        }
        Node->name = pLine[0];
        Node->device_type = search_or_fill(dev_type,dt_);
        Node->battery_capacity=(int)strtol(pLine[1],NULL,10);
        Node->quantity=(int)strtol(pLine[2],NULL,10);
        Node->price=(float) atof(pLine[3]);
        Node->screen_diag=(float) atof(pLine[4]);
        Node->color_in_RGB[0]=(int)strtol(pLine[5],NULL,10);
        Node->color_in_RGB[1]=(int)strtol(pLine[6],NULL,10);
        Node->color_in_RGB[2]=(int)strtol(pLine[7],NULL,10);
        free(pLine);
        hd->last->next=Node;
        hd->first->prev=Node;
        Node->next=NULL;
        Node->prev=hd->last;
        hd->last=Node;
        hd->count++;
        Node->no=hd->count;
        puts("Success! You can see changes in Output.\n");
    }else{
        puts("Something went wrong. Try again.\n");
    }
}

void edit(g_head*hd, dt_head*hdt,int id,int dt){
    char line[100],**pLine,dt_[15];
    gadget *temp;
    temp = (gadget*)malloc(sizeof(gadget));
    getchar();
    bgets(line,100,stdin);
    pLine = split(line,',');
    if(pLine!=NULL && q(line) == 7){
        switch (dt) {
            case 1:
                strcpy(dt_,"phone");
                break;
            case 2:
                strcpy(dt_, "laptop");
                break;
            case 3:
                strcpy(dt_,"tablet");
                break;
            case 4:
                strcpy(dt_,"computer");
        }
        temp = hd->first;
        while (temp->next!=NULL){
            if(temp->no==id){
                temp->name = pLine[0];
                temp->device_type = search_or_fill(hdt,dt_);
                temp->battery_capacity=(int)strtol(pLine[1],NULL,10);
                temp->quantity=(int)strtol(pLine[2],NULL,10);
                temp->price=(float) atof(pLine[3]);
                temp->screen_diag=(float) atof(pLine[4]);
                temp->color_in_RGB[0]=(int)strtol(pLine[5],NULL,10);
                temp->color_in_RGB[1]=(int)strtol(pLine[6],NULL,10);
                temp->color_in_RGB[2]=(int)strtol(pLine[7],NULL,10);
                free(pLine);
            }
            temp=temp->next;
        }
        if(temp->no==id){
            temp->name = pLine[0];
            temp->device_type = search_or_fill(hdt,dt_);
            temp->battery_capacity=(int)strtol(pLine[1],NULL,10);
            temp->quantity=(int)strtol(pLine[2],NULL,10);
            temp->price=(float) atof(pLine[3]);
            temp->screen_diag=(float) atof(pLine[4]);
            temp->color_in_RGB[0]=(int)strtol(pLine[5],NULL,10);
            temp->color_in_RGB[1]=(int)strtol(pLine[6],NULL,10);
            temp->color_in_RGB[2]=(int)strtol(pLine[7],NULL,10);
            free(pLine);
            puts("Success! You can see changes in Output.\n");
        }
    }else{
        puts("Something went wrong. Try again.\n");
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
        if(dt!=NULL){
            dt->name = dtName;
            dt->next=NULL;
            (hdt->last)->next = dt;
            dt->prev = hdt->last;
            hdt->last = dt;
            hdt->count++;
        }
    }
    return dt;
}

int gui(){
    int cmd;
    char * line;
    cmd = -1;
    printf("0 - Info\n"
           "1 - Add new node\n"
           "2 - Edit node by id\n"
           "3 - Delete node by id\n"
           "4 - Output\n"
           "5 - Search by field\n"
           "6 - Sort by field\n"
           "7 - Save & Exit\n");
    line = malloc(10);
    cmd = (int)strtol(fgets(line, 10, stdin), NULL, 10);
    if(!isdigit(*line)){
        cmd=-1;
        puts("Something went wrong. Try again.\n");
    }
    free(line);
    return cmd;
}

void info(){
    puts("Hello! This is my project as course work for programming subject.\n"
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

void save_and_exit(g_head *hd,  FILE *fp){
    gadget *temp;
    if(fp!=NULL){
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
}

void output_dt(dt_head*dt){
    device_type *fak;
    int i;
    i=1;
    printf("Devices: \n");
    for(fak = dt->first; fak != NULL; fak = fak->next) {
        printf("%i - %s \n",i, fak->name);
        i++;
    }
}

int q(char* str){
    int i,c,len;
    len = strlen(str);
    c=0;
    for (i=0;i< len;i++){
        if (str[i]==','){
           c++;
        }
    }
    return c;
}