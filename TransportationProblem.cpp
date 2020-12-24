#include <iostream>
using namespace std;
class Matrix{
private:
    int mRowSize,mColSize,
    Tarray[10][10],
    Shipping[10][10],
    Demand[10],
    Supply[10],
    cmax,
    maxl,
    location[3][7];
    float u[10],
    v[10],
    c[10],
    OSolution,
    Solut;
public:
    Matrix(int a, int b){
        this->mRowSize = a; // Хүснэгтийн мөрийн тоо
        this->mColSize = b; // Хүснэгтийн багана тоо
        this->Solut = 0;
        this->cmax = 0;
        this->maxl = 0;
        this->OSolution = 0;
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                this->Tarray[i][j] = 0;
            }
        }
        for(int i = 0; i < mRowSize; i++){
            this->Demand[i]=0;
        }
        for(int j = 0; j < mColSize; j++){
            this->Supply[j]=0;
        }
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                this->Shipping[i][j] = 0;
            }
        }
        for(int i = 0; i < mRowSize; i++){
            this->u[i]=0;
        }
        for(int j = 0; j < mColSize; j++){
            this->v[j]=0;
        }
        for(int j = 0; j < 6; j++){
            this->c[j]=0;
        }
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 6; j++){
                this->location[i][j]=0;
            }
        }
    }
    void getDemand(){
        for(int i = 0; i < mColSize; i++){
            cout << "Enter demand element " << i << " index ";
            cin >> this->Demand[i];
        }
    }
    void getSupply(){
        for(int i = 0; i < this->mRowSize; i++){
            cout << "Enter supply element " << i << " index " ;
            cin >> this->Supply[i];
        }
    }
    void printfD(){
        for(int i = 0; i < this->mRowSize; i++){
            cout << this->Demand[i] << "\t";
        }
        cout << "\n";
    }
    void printfS(){
        for(int i = 0; i < this->mColSize; i++){
            cout << this->Supply[i] << "\t";
        }
        cout << "\n";
    }
    void get(){
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                cout << "Enter element " << i << " Row " << j << " Column :" ;
                cin >> this->Tarray[i][j];
            }
        }
    }
    void printfM(){
        for(int i=0; i < this->mRowSize; i++){
            for(int j=0; j < this->mColSize; j++){
                cout << this->Tarray[i][j] << "\t";
            }
            cout << "\n";
        }
    }
    void printfSh(){
        for(int i=0; i < this->mRowSize; i++){
            for(int j=0; j < this->mColSize; j++){
                cout << this->Shipping[i][j] << "\t";
            }
            cout << "\n";
        }
    }
    void getShipping(){
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                cout << "Enter element " << i << " Row " << j << " Column :" ;
                cin >> this->Shipping[i][j];
            }
        }
    }
    void Solution(){
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                if(Shipping[i][j] != 0){
                    Solut =Solut + (Shipping[i][j]*Tarray[i][j]);
                }
            }
        }
    }
    void printfSolution(){
        cout << "Solution " << this->Solut << "\n";
    }
    void printfOSolution(){
        cout << "Optimal Solution " << this->OSolution << "\n";
    }
    void printfU(){
        for(int i = 0; i < this->mRowSize; i++){
            cout << this->u[i] << "\t";
        }
        cout << "\n";
    }
    void printfV(){
        for(int i = 0; i < this->mColSize; i++){
            cout << this->v[i] << "\t";
        }
        cout << "\n";
    }
    // Ui + Vj = Cij
    void UVmethod(){
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                if(Shipping[i][j] != 0){
                    if(i != 0 && j == i){
                        u[i]= Tarray[i][j] -v[j];
                    }
                    v[j] = Tarray[i][j] - u[i];
                }
            }
        }
    }
    //Pij = Ui+Vj - Cij
    void p(){
        int k =0;
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                if(Shipping[i][j] == 0){
                    c[k]=this->u[i]+this->v[j]-this->Tarray[i][j];
                    this->location[0][k]=i;
                    this->location[1][k]=j;
                    k++;
                }
            }
        }
    }
    void printfc(){
        for(int i = 0; i < 6; i++){
            cout << this->c[i] << "\t";
        }
        cout <<"\n";
    }
    void maxc(){
        cmax = c[0];
        for(int i = 0; i < 6; i++){
            if(c[i] > cmax && c[i] > 0 ){
                cmax = c[i];
                this->maxl = i;
            }
        }
    }
   void printfLocation(){
        for(int i = 0 ; i < 2 ; i++){
            for(int j = 0; j < 6; j++){
                cout << this->location[i][j] << "\t";
                }
            cout << "\n";
            }
    }
    void Lk(){
        int i = this->location[0][maxl];
        int j = this->location[1][maxl];
        this->Shipping[i][j]=Shipping[i][j]+Shipping[i-1][j];
        this->Shipping[i-1][j+1]=Shipping[i-1][j+1]+Shipping[i-1][j];
        this->Shipping[i][j+1]=Shipping[i][j+1]-Shipping[i-1][j];
        this->Shipping[i-1][j]=0;
    }
    void OptimalSolution(){
        for(int i = 0; i < mRowSize; i++){
            for(int j = 0; j < mColSize; j++){
                if(Shipping[i][j] != 0){
                    OSolution = this->OSolution + (Shipping[i][j]*Tarray[i][j]);
                }
            }
        }
    }
};
int main(){
    int RowSize, ColSize;
    /*Row = 3 */
    cout <<"Matrix row size : " ;
    cin >> RowSize;
    /*Column = 4*/
    cout <<"Matrix Column size: ";
    cin >> ColSize;
    Matrix shippingCosts(RowSize,ColSize);
    cout << "<----------ENTER SHIPPING COSTS----------->\n";
    /*Shipping Costs [ 3 ] [ 1 ] [ 7 ] [ 4 ]
                     [ 2 ] [ 6 ] [ 5 ] [ 9 ]
                     [ 8 ] [ 3 ] [ 3 ] [ 2 ]
    */
    shippingCosts.get();
    /* Зүүн дээд булангийн арга
    /*                                      Supply
      Shipping [ 200 ] [ 50 ] [ 0 ] [ 0 ]  -- 250
               [ 0 ] [ 250 ] [ 100 ] [ 0 ] -- 350
               [ 0 ] [ 0 ] [ 250 ] [ 150 ] -- 400
                --------------------------
     Demand-->  200   300    350     150
    */
    cout << "<-------------ENTER SHIPPING -------------->\n";
    shippingCosts.getShipping();
    /*Demand [200][300][350][150]*/
    //shippingCosts.getDemand();
    /*Supply [250][350][400]*/
    //shippingCosts.getSupply();
    cout << "<----------PRINT SHIPPING COSTS----------->\n";
    shippingCosts.printfM();
    cout << "<--------------PRINT SHIPPING------------->\n";
    shippingCosts.printfSh();
    cout <<"<----------------PRINT DEMAND-------------->\n";
    shippingCosts.printfD();
    cout <<"<----------------PRINT SUPPLY-------------->\n";
    shippingCosts.printfS();
    shippingCosts.Solution();
    cout <<"<----------------PRINT SOLUTION------------->\n";
    shippingCosts.printfSolution();
    shippingCosts.UVmethod();
    cout <<"<-------------------PRINT U----------------->\n";
    shippingCosts.printfU();
    cout <<"<-------------------PRINT V----------------->\n";
    shippingCosts.printfV();
    shippingCosts.p();
    cout <<"<-------------------PRINT C----------------->\n";
    shippingCosts.printfc();
    shippingCosts.maxc();
    cout <<"<------------PRINT MAX LOCATION------------->\n";
    shippingCosts.printfLocation();
    shippingCosts.Lk();
    cout << "<--------------PRINT SHIPPING------------->\n";
    shippingCosts.printfSh();
    shippingCosts.UVmethod();
    cout <<"<-------------------PRINT U----------------->\n";
    shippingCosts.printfU();
    cout <<"<-------------------PRINT V----------------->\n";
    shippingCosts.printfV();
    shippingCosts.p();
    cout <<"<-------------------PRINT C----------------->\n";
    shippingCosts.printfc();
    shippingCosts.maxc();
    cout <<"<------------PRINT MAX LOCATION------------->\n";
    shippingCosts.printfLocation();
    shippingCosts.Lk();
    cout << "<--------------PRINT SHIPPING------------->\n";
    shippingCosts.printfSh();
    shippingCosts.OptimalSolution();
    cout <<"<----------------PRINT SOLUTION------------->\n";
    shippingCosts.printfOSolution();
    return 0;
}
