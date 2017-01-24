1. ergastika monos mou Drettas vasileios(Δρεττας βασιλειος) 1115201300042
2. g++ -o programma main.cpp admin.cpp admin.h forum.cpp forum.h moderator.cpp moderator.h person.cpp person.h post.cpp post.h registerUser.cpp registerUser.h system.cpp system.h thread.cpp thread.h 
3. programma
4. merikes paratiriseis sxetika me tin ylopoihsh ton klaseon gia tin kalyteri katanohsh tou kwdika
Exw xrisimopoihsi tin list tis stl kai iterator gia tin prospelasi tis.
To thread exei mia lista me posts, to forum exei mia lista apo threads kai mia lista apo forums, to system exei mia lista xriston kai mia lista apo forum.
To post exei to ID tou user kai ena reference tou system etsi wste na exei prosvasi sto username tou.
To thread exei reference tou forum sto opoio vriskete etsi wste otan ginete sticked na pigainei stin arxi tis listas twn threads.
To system exei sinartiseis threadID, forumID, threadId, forumId pou lamvanoun os orisma tin ierarxia se string kai epistrefou to antistoixo forum,thread.

Episis exei tis sinartiseis gia fortwsi apo ta arxeia, na simeiwsw oti to loadPost ginete stin loadThread kathos ena thread mporei na einai kleidwmeno kai etsi na min mporoun na mpoun ta post pou eixan dimiourgithei prin to kleidwma tou. Ta thread pou einai kleidwmena mpainoun se mia lista ginete load olwn ton posts kai stin sinexeia ena ena ta thread pou einai stin lista kleidwnontai.

Gia to save ton dedomenwn:to system prospela tin lista ton forum kai kali tin sinartisi save gia kathe forum kathws kai kalei tin sinartisi save gia kathe xristi. Me tin seira tou kathe forum kalei tin sinartisi save gia kathe forum pou periexei kathws kai kathe thread. Telos kathe thread kalei tin sinartisi save gia ta post tou.

To person exei mia lista currentForum me tin ierarxia tou forum pou vriskete, gia paradeigma ama einai sto 1.3.6 tha exei tria ID 1 3 6. Otan pigainei pio vathia kai episkefte kapoio ypoforum tote to ID tou mpainei sto telos tis listas. Episis otan anevainei ena epipedo afaireite to teleutaio stoixeio tis listas. Episis exei to currentThread pou exei to ID tou thread pou vriskete, ama einai -1 tote dn einai sto epipedo tou thread.

To menu gia tin prospelasi olon ton stoixeiwn tou systimatos vriskete sto class tou xristi kathos autos gnwrizei ti leitourgies mporei na kanei. Oi RegisterUser, Modderator kai Admin kleironomoun ta xaraktirika tou proigoumenou tous prosthetontas tis epipleon leitourgies tous.
5.Ksekinisa kataskeuazontas tis klaseis post, thread kai forum, me tis vasikes leitourgies tous get,set, add, move, delete stoixeia ton klasewn. Stin sinexeia eftiaksa tin klasi person xwris to menu, prosthesa tis leitourgies pou mporei na exei. Eftiaksa tis klaseis RegisterUser,Moderattor kai admin me klironomikotita prosthetontas tis leitourgies pou ton ksexwrizoun apo tous diakrinoun apo ta alla eidi. Stin sinexeia eftiaksa to class system xwris tis sinartiseis load apo arxei kai save se arxeio. Stin sinexeia eftiaksa to menu sto Person kai tis ypoklaseis tou. Telos eftiaksa tis leitourgies save kai load arxeio.