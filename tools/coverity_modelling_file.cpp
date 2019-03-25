pthread_mutex_lock(pthread_mutex_t * mutex) {
	int sw;
	if (sw) return EINTR;
	else {
		__coverity_exclusive_lock_acquire__(mutex);
		return 0;
	}
}

pthread_mutex_unlock(pthread_mutex_t * mutex) {
	int sw;
	if (sw) return EINTR;
	else {
		__coverity_exclusive_lock_release__(mutex);
		return 0;
	}
}

