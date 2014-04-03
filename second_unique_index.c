char second_unique_character(char *in_string)
{
  int index = 0, unique_index = 0, found_length = 0;
  char map_of_instances[256]; /* hash */
  char found[256]; /* what was found */
 
  while (index < 256) /* initialize */
  {
    map_of_instances[index] = found[index] = 0;
    index++;
  }
  for (index = 0; in_string[index]; index++) /* parse the string for uniques */
  {
    if (!map_of_instances[in_string[index]])
      found[found_length ++] = in_string[index];
    map_of_instances[in_string[index]] ++; /* how many times present */
  }
  for (index = unique_index = 0; (index < found_length) &&
       (unique_index < 2); index ++) /* so what were our uniques? */
    if (map_of_instances[found[index]] == 1)
       unique_index ++;
  if (unique_index == 2)
    return found[index - 1];
  else /* there weren't two uniques! */
    return 0;
}

