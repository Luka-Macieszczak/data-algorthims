# Bloom Filter

## Bloom filter is used to decide if elements in a stream belong to a set
- Predefine set S which we will query the filter for inclusion (i.e. is element x from the stream in S)
- Use some number of hash functions to set bits in an array to 1 for each element in s based on the hash output
- Since array is a contiguous block of memory, set individual bits instead of values
- When answering a query q, pass it through every hash function, and say q is in S if the bit at hash(q) is always set to 1
- Bloom Filter is a datastructure pre composed from some set
- Consider updates to bloom filter
- Elements in S must be represented as bits and bytes (we are using computers)
- Map bytes instead of a predefined type
## Scratch
- need a way to spawn in hash functions