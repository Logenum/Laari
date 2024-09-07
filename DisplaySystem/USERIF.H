

void UserMes(int iSec,int iLength,char pcMes[]);
int AplMesClass2(int iSec, int iLen, unsigned char *ptmes);
int AplMesClass1(int iSec, int iLen, unsigned char *ptmes);


void USerSecClosed(int iSec);
void USerSecOpened(int iSec);
void  UserConfirm(int iSecondary);
void  UserNack(int iSecondary);
void AplSendUserMes(int iSec,  int iLen, unsigned char cMess[]);
void UserMesSec(int iSec, int iLength, unsigned char cMes[]);

void AplDefineSec(int iSec);




