#include <stdio.h>
#include <string.h>

typedef struct { 
	char login[20];
	char senha[12];
    char email[100];
}usuarios;

int menulogin(){
    printf("----- TELA DE LOGIN -----\n"); 
    printf("Digite 1 para logar\n");
    printf("Digite 2 para cadastrar um novo usuario\n");
    printf("Digite 0 para sair\n");
    printf("----------------------------\n"); 
    int oplogin;
	scanf("%d", &oplogin);
    return oplogin;
}

void cadastrarusuario() {
    int endvalid = 0;
    while(endvalid == 0){
        int valid = 0;
        FILE* file = fopen("usuarios.b", "rb");
        usuarios usuario;
        printf("\n------ CADASTRO DE USUARIO ------\n");
        printf("informe o login\n");
        scanf("%s", usuario.login);
        printf("informe a senha\n");
        scanf("%s", usuario.senha);
        printf("informe o email\n");
        scanf("%s", usuario.email);
        if (strlen(usuario.email) > 80 || strchr(usuario.email, '@') == NULL){
            valid = 1;
            printf("Email inválido!\n");
        }
        usuarios usuario0;
        while (fread(&usuario0, sizeof(usuarios), 1, file)){
            if(strcmp(usuario.login, usuario0.login) == 0 || strcmp(usuario.email, usuario0.email) == 0){
                valid = 1;
                printf("Usuario ou email já existe!\n");
            }
        }
        fclose(file);

        if(valid == 0){
            printf("Cadastro concluido com sucesso!\n");
            if ((file = fopen("usuarios.b", "rb")) == NULL) {
                fclose(file);
                file = fopen("usuarios.b", "wb");
            } else {
                fclose(file);
                file = fopen("usuarios.b", "ab");
            }
            fwrite(&usuario, sizeof(usuarios), 1, file);
            fclose(file);
            endvalid = 1;
        }
    }
}

int login(){
    int check = 0;
    usuarios usuario0;
    printf("\n------ LOGIN DE USUARIO ------\n");
    printf("informe o login\n");
    scanf("%s", usuario0.login);
    printf("informe a senha\n");
    scanf("%s", usuario0.senha);
	FILE* file = fopen("usuarios.b", "rb");
	usuarios usuario;
	while (fread(&usuario, sizeof(usuarios), 1, file)){
		if(strcmp(usuario.login, usuario0.login) == 0 && strcmp(usuario.senha, usuario0.senha) == 0){
			check = 1;
		}
	}
    fclose(file);
    return check;
}

typedef struct { 
	char nome[20];
	char categoria[20];
    float valor;
}gastos;

int menusistema(){
    printf("--------------\n"); 
    printf("Digite 1 para inserir um novo gasto\n");
    printf("Digite 2 para listar os gastos até o momento\n");
    printf("Digite 3 para editar um gasto\n");
    printf("Digite 4 para excluir um gasto\n");
    printf("Digite 5 para buscar e exibir um gasto\n");
    printf("Digite 6 para listar os gastos de uma categoria especifica\n");
    printf("Digite 7 para exibir um resumo dos gastos por categoria\n");
    printf("Digite 8 para inserir/substituir o limite nos gastos\n");
    printf("Digite 9 para exibir o total gasto comparado com o limite\n");
    printf("Digite 10 para exibir os gastos ordenados do maior para o menor\n");
    printf("Digite 11 para excluir todos os gastos e iniciar novamente\n");
    printf("Digite 0 para sair\n");
    printf("----------------------------\n"); 
    int opsistema;
	scanf("%d", &opsistema);
    return opsistema;
}

void cadastrar(){
    int valid = 1;
    while(valid != 0){  
        int valid2 = 0;  
        gastos gasto;
        printf("\n------ CADASTRO DE GASTO ------\n");   
        printf("informe o nome\n");
        scanf("%s", gasto.nome);
        printf("informe a categoria\n");
        scanf("%s", gasto.categoria);
        printf("informe o valor\n");
        scanf("%f", &gasto.valor);
        FILE* file;
        file = fopen("gastos.b", "rb");
        gastos gasto0;
        while (fread(&gasto0, sizeof(gastos), 1, file)){
            if(strcmp(gasto.nome, gasto0.nome) == 0){
                valid2 = 1;
                printf("Ja existe um gasto com esse nome, caso seja a mesma coisa, coloque um numero no final, Ex: Roupa2\n");
            }
        }
        fclose(file);
        if(valid2 == 1){
            valid = 1;
        }else{
            if ((file = fopen("gastos.b", "rb")) == NULL) {
                fclose(file);
                file = fopen("gastos.b", "wb");
            } else {
                fclose(file);
                file = fopen("gastos.b", "ab");
            }
            fwrite(&gasto, sizeof(gastos), 1, file);
            fclose(file);
            valid = 0;
        }
    }
}

void listar(){
    gastos gasto;
    FILE* file = fopen("gastos.b", "rb");
    printf("nome, categoria, valor (em reais):\n");
    while (fread(&gasto, sizeof(gastos), 1, file)){
        printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
    }
    fclose(file);
}

int tamanho(){
    int t = 0;
    gastos gasto;
    FILE* file = fopen("gastos.b", "rb");
    while (fread(&gasto, sizeof(gastos), 1, file)){
        t ++;
    }
    return t;
}

void editar(){
    int t = tamanho();
    int i = 0;
    gastos gasto2[t];
    char nome[20];
    printf("Digite o nome do gasto que você deseja editar:\n");
    scanf("%s", nome);
    printf("----- MENU DE EDIÇÃO -----\n");
    printf("Digite 1 para editar o nome\n");
    printf("Digite 2 para editar a categoria\n");
    printf("Digite 3 para editar o valor\n");
    printf("-----------------------------------\n");
    int op;
    scanf("%d", &op);
    if (op == 1){
        FILE* file = fopen("gastos.b", "rb");
        printf("Digite o novo nome\n");
        char nnome[20];
        scanf("%s", nnome);
        while(fread(&gasto2[i], sizeof(gastos), 1, file)){
		    i++;
        }
        fclose(file);
        file = fopen("gastos.b", "wb");
        for (i = 0; i < t; i ++){
            if(strcmp(gasto2[i].nome, nome) == 0){
                strcpy(gasto2[i].nome, nnome);
            }
            fwrite(&gasto2[i], sizeof(gastos), 1, file);
        }
        fclose(file);
    } else if(op == 2){
        FILE* file = fopen("gastos.b", "rb");
        printf("Digite a nova categoria\n");
        char ncategoria[20];
        scanf("%s", ncategoria);
        while(fread(&gasto2[i], sizeof(gastos), 1, file)){
		    i++;
        }
        fclose(file);
        file = fopen("gastos.b", "wb");
        for (i = 0; i < t; i ++){
            if(strcmp(gasto2[i].nome, nome) == 0){
                strcpy(gasto2[i].categoria, ncategoria);
            }
            fwrite(&gasto2[i], sizeof(gastos), 1, file);
        }
        fclose(file); 
    }else if(op == 3){
        FILE* file = fopen("gastos.b", "rb");
        printf("Digite o novo valor\n");
        float nvalor;
        scanf("%f", &nvalor);
        while(fread(&gasto2[i], sizeof(gastos), 1, file)){
		    i++;
        }
        fclose(file);
        file = fopen("gastos.b", "wb");
        for (i = 0; i < t; i ++){
            if(strcmp(gasto2[i].nome, nome) == 0){
                gasto2[i].valor = nvalor;
            }
            fwrite(&gasto2[i], sizeof(gastos), 1, file);
        }
        fclose(file); 
    }
    printf("Gasto editado com sucesso!\n");
}

void excluir(){
    int t = tamanho();
    int i = 0;
    gastos gasto2[t];
    char nome[20];
    printf("Digite o nome do gasto que você deseja excluir:\n");
    scanf("%s", nome);
    FILE* file = fopen("gastos.b", "rb");
    while(fread(&gasto2[i], sizeof(gastos), 1, file)){
		    i++;
        }
    fclose(file);
    file = fopen("gastos.b", "wb");
    for (i = 0; i < t; i ++){
        if(strcmp(gasto2[i].nome, nome) == 0){
        }else{
            fwrite(&gasto2[i], sizeof(gastos), 1, file);
        }
    }
    fclose(file);
    printf("Gasto excluido com sucesso!\n");
}

void buscar(){
    int valid = 0;
    gastos gasto;
    char nome[20];
    printf("Digite o nome do gasto que você deseja exibir:\n");
    scanf("%s", nome);
    FILE* file = fopen("gastos.b", "rb");
    while(fread(&gasto, sizeof(gastos), 1, file)){
		    if(strcmp(gasto.nome, nome) == 0){
                printf("nome, categoria, valor (em reais):\n");
                printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
                valid = 1;
            }
        }
    if(valid == 0){
        printf("Gasto não encontrado!\n");
    }
    fclose(file);
}

void listarcategoria(){
    int valid = 0;
    gastos gasto;
    char categoria[20];
    printf("Digite o nome da categoria que você deseja listar:\n");
    scanf("%s", categoria);
    FILE* file = fopen("gastos.b", "rb");
    printf("nome, categoria, valor (em reais):\n");
    while(fread(&gasto, sizeof(gastos), 1, file)){
		    if(strcmp(gasto.categoria, categoria) == 0){
                printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
                valid = 1;
            }
        }
    if(valid == 0){
        printf("Não existe nenhum gasto dessa categoria!\n");
    }
    fclose(file);
}

typedef struct {
    char categoria[20];
    float valor;
}categorias;

void resumo(){
    int t = tamanho();
    int i, j = 0;
    categorias categoriatemporario[t];
    gastos gasto;
    int valid = 0;
    for(i = 0; i < t; i++){
        strcpy(categoriatemporario[i].categoria, "---");
    }
    FILE* file = fopen("gastos.b", "rb");
    while(fread(&gasto, sizeof(gastos), 1, file)){
        for(i = 0; i < t; i++){
            if(strcmp(gasto.categoria, categoriatemporario[i].categoria) == 0){
                valid = 1;
            }
        }
        if (valid == 0){
            strcpy(categoriatemporario[j].categoria, gasto.categoria);
            j ++;
        }
        valid = 0;
    }
    categorias categoria[j + 1];
    for(i = 0; i < j; i++){
        strcpy(categoria[i].categoria, categoriatemporario[i].categoria);
        categoria[i].valor = 0;
    }
    fclose(file);
    file = fopen("gastos.b", "rb");
    while(fread(&gasto, sizeof(gastos), 1, file)){
        for(i = 0; i < j; i++){
            if(strcmp(gasto.categoria, categoria[i].categoria) == 0){
                categoria[i].valor = categoria[i].valor + gasto.valor;
            }
        }
    }
    float gastototal = 0;
    printf("--- SEGUE O TOTAL GASTO POR CATEGORIA E O GASTO TOTAL ---\n");
    printf("--- TOTAL GASTO POR CATEGORIA ---\n");
    printf("categoria, gasto por categoria (em reais)\n");
    for(i = 0; i < j; i++){
        printf("%s, %f\n", categoria[i].categoria, categoria[i].valor);
        gastototal = gastototal + categoria[i].valor;
    }
    printf("\n--- GASTO TOTAL ---\n");
    printf("%f reais\n", gastototal);
    fclose(file);
}

void definirlimite(){
    FILE* file = fopen("limite.b", "wb");
    printf("Digite o limite dos gastos\n");
    float limite;
    scanf("%f", &limite);
    fwrite(&limite, sizeof(float), 1, file);
    printf("Limite de %f reais definido!\n", limite);
    fclose(file);
}

void gastoxlimite(){
    FILE* file = fopen("limite.b", "rb");
    float limite;
    fread(&limite, sizeof(float), 1, file);
    fclose(file);
    FILE* file2 = fopen("gastos.b", "rb");
    float gastototal = 0;
    gastos gasto;
    while(fread(&gasto, sizeof(gastos), 1, file)){
        gastototal = gastototal + gasto.valor;
    }
    float perc = (gastototal / limite) * 100;
    if (perc > 100){
        printf("Você já gastou %f reais, o que representa %f pontos percentuais do seu limite de %f reais e acabou passando dele\n", gastototal, perc, limite);
    }else{
        printf("Você já gastou %f reais, o que representa %f pontos percentuais do seu limite de %f reais e ainda não passou dele\n", gastototal, perc, limite);
    }
    fclose(file2);
}

void maiorparamenor(){
    FILE* file = fopen("gastos.b", "rb");
    int t = tamanho();
    gastos gasto[t];
    gastos temp;
    int j, i = 0;
    while(fread(&gasto[i], sizeof(gastos), 1, file)){
		i++;
    }
    fclose(file);
    for(i = 0; i < t; i ++){
        for(j = i + 1; j < t; j ++){
            if(gasto[j].valor > gasto[i].valor){
                temp = gasto[j];
                gasto[j] = gasto[i];
                gasto[i] = temp;
            }
        }
    }
    printf("Segue os gastos ordenados do maior para o menor:\n");
    printf("nome, categoria, valor (em reais):\n");
    for(i = 0; i < t; i ++){
        printf("%s, %s, %f\n", gasto[i].nome, gasto[i].categoria, gasto[i].valor);
    }
}

void iniciarnovamente(){
    printf("Você tem certeza que deseja excluir os gastos e iniciar novamente?\nDIGITE 1 PARA SIM E 0 PARA NÃO\n");
    int confirm;
    scanf("%d", &confirm);
    gastos gasto;
    if(confirm == 1){
        printf("----- GASTOS EXCLUIDOS, INICIE COM UM NOVO GASTO -----:\n");
        FILE* file = fopen("gastos.b", "wb");
        printf("\n--------------- CADASTRO DE GASTO ---------------\n");   
        printf("informe o nome\n");
        scanf("%s", gasto.nome);
        printf("informe a categoria\n");
        scanf("%s", gasto.categoria);
        printf("informe o valor\n");
        scanf("%f", &gasto.valor);
        fwrite(&gasto, sizeof(gastos), 1, file);
        fclose(file);
    }else{
        printf("Voltando para o menu incial...");
    }

}

int main(){
    int oplogin = menulogin();
    while(oplogin != 0){
    	if (oplogin == 1){
            int b = login();
            if(b == 1){
                printf("--- LOGIN BEM SUCEDIDO ---\n");
                printf("----------------------------------- \nSeja bem vindo ao sistema de gerenciamente e controle financeiro do meu encommerce, aqui \nvocê pode registrar e acompanhar os seus gastos para um melhor controle das despesas!\n -----------------------------------\n");
                int opsistema = menusistema();
                while(opsistema != 0){
                    if(opsistema == 1){
                        cadastrar();
                        opsistema = menusistema();
                    }else if(opsistema == 2){
                        listar();
                        opsistema = menusistema();
                    }else if(opsistema == 3){
                        editar();
                        opsistema = menusistema();
                    }else if(opsistema == 4){
                        excluir();
                        opsistema = menusistema();
                    }else if(opsistema == 5){
                        buscar();
                        opsistema = menusistema();
                    }else if(opsistema == 6){
                        listarcategoria();
                        opsistema = menusistema();
                    }else if(opsistema == 7){
                        resumo();
                        opsistema = menusistema();
                    }else if(opsistema == 8){
                        definirlimite();
                        opsistema = menusistema();
                    }else if(opsistema == 9){
                        gastoxlimite();
                        opsistema = menusistema();
                    }else if(opsistema == 10){
                        maiorparamenor();
                        opsistema = menusistema();
                    }else if(opsistema == 11){
                        iniciarnovamente();
                        opsistema = menusistema();
                    }
                }
                oplogin = 0;
            }
            else if(b == 0){
                printf("--- LOGIN INVÁLIDO ---\n");
                oplogin = menulogin();
            }
            }
            else if(oplogin == 2){
                cadastrarusuario();
                oplogin = menulogin();
            }
        }
    }

#include <stdio.h>
#include <string.h>

typedef struct { 
    char login[20];
    char senha[12];
    char email[100];
} usuarios;

// Função para mesclar duas metades
void merge(usuarios arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    usuarios L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].login, R[j].login) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função principal do mergesort
void mergesort(usuarios arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Função para listar os usuários em ordem
void listarUsuariosOrdenados() {
    FILE* file = fopen("usuarios.b", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Contar quantos usuários existem
    fseek(file, 0, SEEK_END);
    int numUsuarios = ftell(file) / sizeof(usuarios);
    fseek(file, 0, SEEK_SET);

    usuarios lista[numUsuarios];

    for (int i = 0; i < numUsuarios; i++) {
        fread(&lista[i], sizeof(usuarios), 1, file);
    }
    fclose(file);

    // Ordenar os usuários usando mergesort
    mergesort(lista, 0, numUsuarios - 1);

    // Exibir os usuários ordenados
    printf("\n------ LISTA DE USUÁRIOS ORDENADA ------\n");
    for (int i = 0; i < numUsuarios; i++) {
        printf("Login: %s, Email: %s\n", lista[i].login, lista[i].email);
    }
    printf("-----------------------------------------\n");
}

#include <stdio.h>
#include <string.h>

typedef struct { 
    char login[20];
    char senha[12];
    char email[100];
} usuarios;

// Função para mesclar duas metades (mergesort)
void merge(usuarios arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    usuarios L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].login, R[j].login) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função principal do mergesort
void mergesort(usuarios arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Função para busca binária
int buscaBinaria(usuarios arr[], int left, int right, char* loginProcurado) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        int comparacao = strcmp(arr[mid].login, loginProcurado);
        
        if (comparacao == 0) {
            return mid; // Encontrou o login
        } else if (comparacao < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Login não encontrado
}

// Função para listar os usuários em ordem e buscar um específico
void listarEBuscarUsuario() {
    FILE* file = fopen("usuarios.b", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Contar quantos usuários existem
    fseek(file, 0, SEEK_END);
    int numUsuarios = ftell(file) / sizeof(usuarios);
    fseek(file, 0, SEEK_SET);

    usuarios lista[numUsuarios];

    for (int i = 0; i < numUsuarios; i++) {
        fread(&lista[i], sizeof(usuarios), 1, file);
    }
    fclose(file);

    // Ordenar os usuários usando mergesort
    mergesort(lista, 0, numUsuarios - 1);

    // Exibir os usuários ordenados
    printf("\n------ LISTA DE USUÁRIOS ORDENADA ------\n");
    for (int i = 0; i < numUsuarios; i++) {
        printf("Login: %s, Email: %s\n", lista[i].login, lista[i].email);
    }
    printf("-----------------------------------------\n");

    // Solicitar o login para buscar
    char loginProcurado[20];
    printf("Digite o login que deseja buscar: ");
    scanf("%s", loginProcurado);

    // Realizar a busca binária
    int resultado = buscaBinaria(lista, 0, numUsuarios - 1, loginProcurado);

    if (resultado != -1) {
        printf("Usuário encontrado! Login: %s, Email: %s\n", lista[resultado].login, lista[resultado].email);
    } else {
        printf("Usuário não encontrado.\n");
    }
}

int main() {
    listarEBuscarUsuario();
    return 0;
}