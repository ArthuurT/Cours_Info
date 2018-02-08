void *pTicketAllouer(int uCardinalMax);//O(nCardinalMax)
void TicketAMORCER();
int nTicketCardinal(void *pTicket);//O(1)
int bTicketContient(void *pTicket,int uTicket);//O(1)
void TicketINITIALISER();
void TicketRestituer(void *pTicket);//O(1)
void TicketRetirer(void *pTicket,int uTicket);//O(1)
void TicketRetirer0(void *pTicket0,int uTicket0,void *pTicket,int uTicket);//O(1)
int uTicketSuivant(void *pTicket);//O(1)
void TicketTESTER(int iTest);
void TicketVisionner(char *sMessage,void *pTicket);//O(nCardinalMax)
void TicketVoir(char *sMessage,void *pTicket);//O(nCardinalMax)
