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

    printf("Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(&village->_villager_message);
        village->_druid->_pot_size = village->_druid->_max_pot_size;
        village->_druid->_nb_refills -= 1;
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware %s%lu%s",
            "I can only make ", village->_druid->_nb_refills,
                " more refills after this one.\n");
        sem_post(&village->_druid_message);
        if (!village->_druid->_nb_refills)
            break;
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}

static void interact_with_mutex(size_t thread_id, village_t *village)
{
    pthread_mutex_lock(&village->_pot);
    if (!village->_pot_status) {
        pthread_mutex_unlock(&village->_pot);
        return;
    }
    printf("Villager %lu: I need a drink... I see %i servings left.\n",
        thread_id, village->_druid->_pot_size);
    if (village->_druid->_pot_size <= 0) {
        printf("Villager %lu: Hey Pano wake up! We need more potion.\n",
            thread_id);
        sem_post(&village->_villager_message);
        sem_wait(&village->_druid_message);
    }
    village->_druid->_pot_size--;
    if (!village->_druid->_pot_size && !village->_druid->_nb_refills)
        village->_pot_status = false;
    pthread_mutex_unlock(&village->_pot);
}

void *villager_thread(void *_village)
{
    village_t *village = *(village_t **)_village;
    size_t thread_id = village->_thread_id;

    village->_villagers[thread_id]->_id = thread_id;
    village->_thread_id = NEGATIVE_NUMBER;
    while (1) {
        if (!village->_villagers[thread_id]->_nb_fights_left ||
            !(village->_pot_status))
            break;
        printf("Villager %lu: Going into battle!\n", thread_id);
        interact_with_mutex(thread_id, village);
        village->_villagers[thread_id]->_nb_fights_left -= 1;
        printf("Villager %lu: Take that roman scum! Only %lu left.\n",
            thread_id, village->_villagers[thread_id]->_nb_fights_left);
    }
    printf("Villager %lu: I'm going to sleep now.\n", thread_id);
    return NULL;
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
    for (size_t i = 0; i < village->_nb_villagers; i++) {
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
    village->_pot_status = true;
    init_villagers(village, pot_size, nb_refills, nb_fights);
    village->_thread_id = NEGATIVE_NUMBER;
    pthread_mutex_init(&village->_pot, NULL);
    sem_init(&village->_druid_message, 0, 0);
    sem_init(&village->_villager_message, 0, 0);
    return village;
}

int launch_village(size_t *args)
{
    village_t *village = build_village(args[0], args[1], args[2], args[3]);

    pthread_mutex_lock(&village->_pot);
    pthread_create(&village->_druid_thread, NULL, druid_thread,
        (void *)&village);
    for (size_t i = 0; i < village->_nb_villagers; i++) {
        village->_thread_id = i;
        pthread_create(&village->_villagers_thread[i], NULL, villager_thread,
            (void *)&village);
        while (village->_thread_id != NEGATIVE_NUMBER);
    }
    pthread_mutex_unlock(&village->_pot);
    pthread_join(village->_druid_thread, NULL);
    for (size_t i = 0; i < village->_nb_villagers; i++)
        pthread_join(village->_villagers_thread[i], NULL);
    pthread_mutex_destroy(&village->_pot);
    sem_destroy(&village->_druid_message);
    sem_destroy(&village->_villager_message);
    return 0;
}
