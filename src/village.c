/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** village
*/

#include "includes.h"

void *druid_thread(void *_village)
{
    village_t *village = *(village_t **)_village;
    size_t thread_id = 0;

    printf("Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(&village->_villager_message);
        pthread_mutex_lock(&village->_pot);
        village->_druid->_pot_size = village->_druid->_max_pot_size;
        village->_druid->_nb_refills -= 1;
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I%s%i%s",
            " can only make ", village->_druid->_nb_refills,
                " more refills after this one.\n");
        if (!village->_druid->_nb_refills) {
            printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
            village->_pot_status = false;
        }
        pthread_mutex_unlock(&village->_pot);
        sem_post(&village->_druid_message);
        if (!village->_druid->_nb_refills)
            break;
    }
}

void *villager_thread(void *_village)
{
    village_t *village = *(village_t **)_village;
    size_t thread_id = village->_thread_id;

    village->_villagers[thread_id]->_id = thread_id;
    village->_thread_id = NEGATIVE_NUMBER;
    while (1) {
        printf("Villager %lu: Going into bttle!\n", thread_id);
        pthread_mutex_lock(village->_whos_talking);
        printf("Villager %lu: I need a drink... I see %lu servings left.\n", thread_id, village->_druid->_pot_size);
        if (!village->_nb_fight_left)
            break;
        village->_message = DRUID_GIVE_POTION;
        sem_post(village->_sent_message);
        sem_wait(village->_sent_response);
        message = village->_message;
        if (message == VILLAGER_NO_MORE_POTION) {
            printf("Villager %lu: Hey Pano wake up! We need more potion.\n", thread_id);
            village->_message = DRUID_POT_EMPTY;
            sem_post(village->_sent_message);
            sem_wait(village->_sent_response);
        }
        pthread_mutex_unlock(village->_whos_talking);
        if (message == VILLAGER_NO_MORE_REFFILS)
            break;
        if (message == VILLAGER_HERE_YOU_GO) {
            printf("Villager %lu: Take that roman scum! Only %lu left.\n",
                thread_id, village->_nb_fight_left);
            village->_nb_fight_left--;
        }
    }
    printf("Villager %lu: I'm going to sleep now.\n", thread_id);
}

static void init_villagers(village_t *village, size_t pot_size,
    size_t nb_refills, size_t nb_fights)
{
    village->_druid = (druid_t *)f_malloc(sizeof(druid_t));
    village->_druid->_max_pot_size = pot_size;
    village->_druid->_pot_size = village->_druid->_max_pot_size;
    village->_druid->_nb_refills = nb_refills;
    village->_druid_thread = ((pthread_t)-1);
    village->_villagers_thread = (pthread_t *)f_malloc(sizeof(pthread_t) *
        village->_nb_villagers);
    village->_villagers = (villager_t **)f_malloc((sizeof(villager_t *) *
        village->_nb_villagers));
    for (int i = 0; i < village->_nb_villagers; i++) {
        village->_villagers[i] = (villager_t *)f_malloc(sizeof(villager_t));
        village->_villagers[i]->_nb_fights_left = nb_fights;
        village->_villagers_thread[i] = ((pthread_t)-1);
    }
}

static village_t *build_village(size_t nb_villagers, size_t pot_size,
    size_t nb_fights, size_t nb_refills)
{
    village_t *village = (village_t *)f_malloc(sizeof(village_t));

    village->_nb_villagers = nb_villagers;
    init_villagers(village, pot_size, nb_refills, nb_fights);
    village->_thread_id = NEGATIVE_NUMBER;
    pthread_mutex_init(&village->_pot, NULL);
    return village;
}

int launch_village(size_t *args)
{
    village_t *village = build_village(args[0], args[1], args[2], args[3]);

    pthread_mutex_lock(&village->_pot);
    pthread_create(&village->_druid_thread, NULL, druid_thread, (void *)&village);
    for (size_t i = 0; i < village->_nb_villagers; i++) {
        village->_thread_id = i;
        pthread_create(&village->_villagers_thread[i], NULL, villager_thread, (void *)&village);
        while (village->_thread_id != NEGATIVE_NUMBER);
    }
    pthread_mutex_unlock(&village->_pot);
    pthread_join(village->_druid_thread, NULL);
}
