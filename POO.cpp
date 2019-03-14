#include<iostream>
struct nod{
char c;
nod *urm,*tr;
};
class nr_i_mari{
    friend class nr_r_mari;
private:
    nod *x;
    char s,k;
protected:
public:
    nr_i_mari();
    void clean();
    ~nr_i_mari();
    friend std::istream& operator >> (std::istream &input,nr_i_mari &a);
    friend std::ostream& operator << (std::ostream &output,nr_i_mari &a);
    int operator > (nr_i_mari &b);
    nr_i_mari operator + (nr_i_mari &b);
    nr_i_mari operator - (nr_i_mari &b);
    nr_i_mari operator ^ (int n);
    nr_i_mari operator * (nr_i_mari &b);
    int cif();
    void add_s(int n);
    void add_i(int n);
    friend nr_i_mari convert(int n);
    friend int convert_back(nr_i_mari a);
    int nr_cif();
};
class nr_r_mari{
private:
    nr_i_mari i,e;
    char k;
protected:
public:
    nr_r_mari();
    ~nr_r_mari();
    friend std::istream& operator >> (std::istream &input,nr_r_mari &a);
    friend std::ostream& operator << (std::ostream &output,nr_r_mari &a);
    nr_r_mari operator * (nr_r_mari &b);
    nr_r_mari operator + (nr_r_mari &b);
    balance();
};
nr_i_mari::nr_i_mari()
{
    x=NULL;
    k=1;
}
void nr_i_mari::clean()
{
    if(x==NULL)
        return;
    while(x->urm!=NULL)
    {
        x=x->urm;
        delete x->tr;
    }
    delete x;
    x=NULL;
}
nr_i_mari::~nr_i_mari()
{
    if(k!=0)
        clean();
}
std::istream& operator >> (std::istream &input,nr_i_mari &a)
{
    a.clean();
    char c;
    input>>std::noskipws>>c;
    nod *y=new nod;
    a.x=y;
    y->tr=y->urm=NULL;
    if(c=='+' || c=='-')
    {
        a.s=c;
        input>>std::noskipws>>c;
    }
    else
        a.s='+';
    if(a.s=='+')
        a.s=1;
    else
        a.s=-1;
    y->c=c-'0';
    input>>std::noskipws>>c;
    while(c!='\n')
    {
        nod *z=new nod;
        z->urm=y;
        z->tr=NULL;
        y->tr=a.x=z;
        z->c=c-'0';
        y=z;
        input>>std::noskipws>>c;
    }
    return input;
}
std::ostream& operator << (std::ostream &output,nr_i_mari &a)
{
    nod *y=a.x;
    if(a.s==-1)
        output<<'-';
    while(y->urm!=NULL)
        y=y->urm;
    while(y!=NULL)
    {
        output<<(int)y->c;
        y=y->tr;
    }
    return output;
}
int nr_i_mari::operator > (nr_i_mari &b)
{
    nod *aux=x,*y=b.x;
    while(aux->urm!=NULL && y->urm!=NULL)
    {
        aux=aux->urm;
        y=y->urm;
    }
    if(aux->urm!=NULL)
        return 1;
    if(y->urm!=NULL)
        return -1;
    while(aux->tr!=NULL && y->tr!=NULL && aux->c==y->c)
    {
        aux=aux->tr;
        y=y->tr;
    }
    if(aux->c==y->c)
        return 0;
    if(aux->c>y->c)
        return 1;
    return -1;
}
nr_i_mari nr_i_mari::operator + (nr_i_mari &b)
{
    nr_i_mari a;
    a.k=0;
    if(s==b.s)
    {
        int k=0;
        a.s=s;
        a.x=new nod;
        nod *aux=x,*y=b.x,*z=a.x;
        z->urm=z->tr=NULL;
        z->c=(x->c+y->c+k)%10;
        k=(x->c+y->c+k)/10;
        while(x->urm!=NULL && y->urm!=NULL)
        {
            nod *t=new nod;
            t->tr=z;
            t->urm=NULL;
            z->urm=t;
            x=x->urm;
            y=y->urm;
            t->c=(x->c+y->c+k)%10;
            k=(x->c+y->c+k)/10;
            z=t;
        }
        while(x->urm!=NULL)
        {
            nod *t=new nod;
            t->tr=z;
            t->urm=NULL;
            z->urm=t;
            x=x->urm;
            t->c=(x->c+k)%10;
            k=(x->c+k)/10;
            z=t;
        }
        while(y->urm!=NULL)
        {
            nod *t=new nod;
            t->tr=z;
            t->urm=NULL;
            z->urm=t;
            y=y->urm;
            t->c=(y->c+k)%10;
            k=(y->c+k)/10;
            z=t;
        }
        if(k==1)
        {
            nod *t=new nod;
            t->tr=z;
            t->urm=NULL;
            z->urm=t;
            t->c=1;
        }
        x=aux;
        return a;
    }
    if((*this>b)==-1)
    {
        a=b+(*this);
        return a;
    }
    int k=0;
    a.x=new nod;
    a.s=s;
    nod *aux=x,*y=b.x,*z=a.x;
    z->urm=z->tr=NULL;
    z->c=(10+x->c-y->c-k)%10;
    if(x->c<y->c+k)
        k=1;
    while(x->urm!=NULL && y->urm!=NULL)
    {
        nod *t=new nod;
        t->tr=z;
        t->urm=NULL;
        z->urm=t;
        x=x->urm;
        y=y->urm;
        t->c=(10+x->c-y->c-k)%10;
        if(x->c<y->c+k)
            k=1;
        else
            k=0;
        z=t;
    }
    while(x->urm!=NULL)
    {
        nod *t=new nod;
        t->tr=z;
        t->urm=NULL;
        z->urm=t;
        x=x->urm;
        t->c=(10+x->c-k)%10;
        if(x->c<k)
            k=1;
        else
            k=0;
        z=t;
    }
    while(z->tr!=NULL && z->c==0)
    {
        z=z->tr;
        delete z->urm;
        z->urm=NULL;
    }
    x=aux;
    return a;
}
nr_i_mari nr_i_mari::operator - (nr_i_mari &b)
{
    b.s=-b.s;
    nr_i_mari a=*this+b;
    b.s=-b.s;
    a.k=0;
    return a;
}
nr_i_mari nr_i_mari::operator ^ (int b)
{
    nr_i_mari a;
    a.x=new nod;
    a.s=s;
    a.k=0;
    nod *aux=x,*y=a.x;
    y->urm=y->tr=NULL;
    y->c=aux->c;
    while(aux->urm!=NULL)
    {
        aux=aux->urm;
        nod *z=new nod;
        z->urm=NULL;
        z->tr=y;
        y->urm=z;
        y=z;
        z->c=aux->c;
    }
    while(b!=0)
    {
        b--;
        nod *z=new nod;
        z->tr=NULL;
        z->urm=a.x;
        a.x->tr=z;
        z->c=0;
        a.x=z;
    }
    return a;
}
nr_i_mari nr_i_mari::operator * (nr_i_mari &b)
{
    if(*this>b==-1)
        return b*(*this);
    nr_i_mari c[10],a;
    c->s=1;
    c->x=new nod;
    c->x->urm=c->x->tr=NULL;
    c->x->c=0;
    for(int i=1;i<10;i++)
        c[i]=c[i-1]+(*this);
    nod *y=b.x;
    a=c[y->c]^0;
    int e=1;
    while(y->urm!=NULL)
    {
        y=y->urm;
        nr_i_mari b=c[y->c]^e;
        a=a+b;
        e++;
    }
    a.k=0;
    return a;
}
int nr_i_mari::cif()
{
    if(x->urm==NULL)
        return 0;
    if(x->c==0)
    {
        nod *y=x;
        x=x->urm;
        x->tr=NULL;
        delete y;
        return cif()+1;
    }
    return 0;
}
void nr_i_mari::add_i(int n)
{
    if(x==NULL)
    {
        x=new nod;
        x->urm=x->tr=NULL;
        x->c=n;
        return;
    }
    nod *y=new nod;
    y->urm=x;
    y->tr=NULL;
    x->tr=y;
    y->c=n;
    x=y;
}
void nr_i_mari::add_s(int n)
{
    if(x==NULL)
    {
        x=new nod;
        x->urm=x->tr=NULL;
        x->c=n;
        return;
    }
    nod *y=new nod,*aux=x;
    while(x->urm!=NULL)
        x=x->urm;
    y->urm=NULL;
    y->tr=x;
    x->urm=y;
    y->c=n;
    x=aux;
}
nr_i_mari convert(int n)
{
    nr_i_mari a;
    a.k=0;
    if(n<0)
    {
        a.s=-1;
        n=-n;
    }
    else
        a.s=1;
    a.add_s(n%10);
    while(n/10!=0)
    {
        n=n/10;
        a.add_s(n%10);
    }
    return a;
}
int convert_back(nr_i_mari a)
{
    int x=0;
    nod *y=a.x;
    while(y!=NULL)
    {
        x=x*10+y->c;
        y=y->urm;
    }
    if(a.s==-1)
        return -x;
    return x;
}
int nr_i_mari::nr_cif()
{
    int k=0;
    nod *aux=x;
    while(aux!=NULL)
    {
        k++;
        aux=aux->urm;
    }
    return k;
}
nr_r_mari::nr_r_mari()
{
    k=1;
}
nr_r_mari::~nr_r_mari()
{
    if(k==0)
    {
        i.~nr_i_mari();
        e.~nr_i_mari();
    }
}
std::istream& operator >> (std::istream &input,nr_r_mari &a)
{
    input>>a.i>>a.e;
    int n=a.i.cif();
    nr_i_mari b=convert(n);
    a.e=a.e+b;
    return input;
}
std::ostream& operator << (std::ostream &output,nr_r_mari &a)
{
    output<<a.i<<"e"<<a.e;
    return output;
}
nr_r_mari nr_r_mari::operator * (nr_r_mari &b)
{
    nr_r_mari c;
    c.i=i*b.i;
    c.e=e+b.e;
    int n=c.i.cif();
    nr_i_mari d=convert(n);
    c.e=c.e+d;
    return c;
}
nr_r_mari nr_r_mari::operator + (nr_r_mari &b)
{
    int dif=i.nr_cif()-b.i.nr_cif();
    nr_i_mari a=convert(dif);
    a=a+e;
    a=a-b.e;
    int n=convert_back(a);
    if(n>30 || n<-30)
    {
        std::cout<<"DA";
        if(a.s==-1)
        {
            nr_i_mari aux=convert(0);
            nr_r_mari r;
            r.e=b.e+aux;
            r.i=b.i+aux;
            r.k=0;
            return r;
        }
        else
        {
            nr_i_mari aux=convert(0);
            nr_r_mari r;
            r.e=e+aux;
            r.i=i+aux;
            r.k=0;
            return r;
        }
    }
    n=n-dif;
    if(n<0)
    {
        for(int u=n;u<0;u++)
            b.i.add_i(0);
        nr_i_mari aux=convert(0);
        nr_r_mari r;
        r.e=e+aux;
        r.i=i+b.i;
        r.k=0;
        b.i.cif();
        return r;
    }
    else
    {
        for(int u=n;u>0;u--)
            i.add_i(0);
        nr_i_mari aux=convert(0);
        nr_r_mari r;
        r.e=b.e+aux;
        r.i=i+b.i;
        r.k=0;
        i.cif();
        return r;
    }
}
int main()
{
    nr_r_mari a,b,c;
    std::cin>>a>>b;
    c=a+b;
    std::cout<<a<<" "<<b<<" "<<c;
    return 0;
}
