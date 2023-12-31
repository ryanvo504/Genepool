# Gene Pool

This is a database program that stores a collection of
people and  their biological relatives.  You can then search this database based
on the relationships between the people it contains.

The `main.cpp` file handles the
main input-output loop,  and the `Query.*` files handle parsing, validating, and
executing queries.
```
[iris@olympus genepool]$ ./genepool data/Cunco.tsv
> Kind's mother
 - Rainbow Lake
> Kind's siblings
 - Danehill Dancer
> Saintly_Speech's maternal ancestors
 (no results)
> Well_Spoken's maternal ancestors
 - Saintly Speech
> Well_Spoken paternal ancestors
 - Fairy Bridge
 - Northern Dancer
 - Sadlers Wells
```

### Reading the Data

This program  will be passed one argument on the command line.  This is the path
to  a file containing  some genealogical data.  The `main()` function  will open
this file and pass it as a `std::istream` to your `GenePool` constructor.

The data is in a slightly modified TSV (tab-separated values) format, one person
per line.  However, some lines should be ignored:

- Lines that start with the hash sign (`#`) are comments.
- Empty lines are included for spacing and readability.

All other lines are data.  They will consist of four strings,  separated by tabs
(the `'\t'` character in C, ASCII value 0x09). These strings may contain spaces.
They are, in order:

- The name of a person.
- The gender of the person, either `male` or `female`.
- The name of the person's mother, or `???` if unknown.
- The name of the person's father, or `???` if unknown.

You may assume  that data lines  will always be valid.  There will never be more
than one person with any given name,  and people will always appear later in the
file than their parents.


### Querying the Data

Once you've read in the entire data file,  the program will prompt the user and
then wait for input, which will come in this format (not all modifiers are valid
for all relationships; see the next section for details):

```
[name]'s [parent-modifier] [sibling-modifier] [relationship]
```

- `name` is the name of a person in the database; the `'s` is optional.
- `parent-modifier` is an optional relationship modifier; it can be either
  `maternal` or `paternal`.
- `sibling-modifier` is an optional relationship modifier; it can be either
  `full` or `half`.
- `relationship` is one of the relationships described in the next section.

The program parses the query,  executes it against your database, and then
prints the result, listing the people it has found in alphabetical order. If an error
occurs,  it will print the error message instead.  Finally, it will re-print
the prompt and wait for more input.  Repeat this loop until you reach the end of
the input stream.

## Relationships

All the relationships you'll be dealing with are biological ones. You can assume
that all people have exactly two biological parents - one mother and one father.
You can also ignore all non-biological relationships:  you won't need to support
queries for spouses, in-laws, step-siblings, etc.  The relationships you do need
to support are explained below.

- Your **mother** is your female parent.
- Your **father** is your male parent.
- Your **parents** are your mother and your father.
  - Your **maternal** parent is your mother.
  - Your **paternal** parent is your father.

- Your **grandparents** are the parents of your parents.
  - Your **maternal** grandparents are your mother's parents.
  - Your **paternal** grandparents are your father's parents.

- Your **children** are the people who have you as a parent.
- Your **sons** are your male children.
- Your **daughters** are your female children.

- Your **grandchildren** are your children's children.
- Your **grandsons** are your male grandchildren.
- Your **granddaughters** are your female grandchildren.

- Your **siblings** are people who share a parent with you, but are not you.
  - Your **maternal** siblings have the same mother as you.
  - Your **paternal** siblings have the same father as you.
  - Your **full** siblings have the same mother and father as you.
  - Your **half** siblings share only one parent with you.
- Your **brothers** are your male siblings.
- Your **sisters** are your female siblings.

- Your **nieces** are the daughters of your siblings.
  - Your **maternal** nieces are the daughters of your maternal siblings.
  - Your **paternal** nieces are the daughters of your paternal siblings.
  - Your **full** nieces are the daughters of your full siblings.
  - Your **half** nieces are the daughters of your half siblings.

- Your **nephews** are the sons of your siblings.
  - Your **maternal** nephews are the sons of your maternal siblings.
  - Your **paternal** nephews are the sons of your paternal siblings.
  - Your **full** nephews are the sons of your full siblings.
  - Your **half** nephews are the sons of your half siblings.

- Your **aunts** are your parents' sisters.
  - Your **maternal** aunts are your mother's sisters.
  - Your **paternal** aunts are your father's sisters.
  - Your **full** aunts your parents' full sisters.
  - Your **half** aunts your parents' half sisters.

- Your **uncles** are your parents' brothers.
  - Your **maternal** uncles are your mother's brothers.
  - Your **paternal** uncles are your father's brothers.
  - Your **full** uncles your parents' full brothers.
  - Your **half** uncles your parents' half brothers.

- Your **cousins** are the children of your aunts and uncles.
  - Your **maternal** cousins are the children of your mother's siblings.
  - Your **paternal** cousins are the children of your father's siblings.
  - Your **full** cousins are the children of your parents' full siblings.
  - Your **half** cousins are the children of your parents' half siblings.

- Your **ancestors** are your parents, your parents' parents, and so on.
  - Your **maternal** ancestors are your mother and her ancestors.
  - Your **paternal** ancestors are your father and his ancestors.
- Your **descendants** are your children, your children's children, and so on.


### Edge Cases

People can only have relationships through known parents. People with completely
unknown parents should never be considered  siblings.  People need  at least one
known parent in common before they can be treated as siblings.

People who have an unknown father have no paternal siblings. The same applies to
maternal siblings  when the mother is unknown.  You can only have  a maternal or
paternal relationship through a known parent.

Siblings who share one known parent and have the other parent unknown  should be
considered half siblings. For example, if Alice and Bob are both the children of
Eve and an unknown father, they should be treated as half siblings.

People can show up in multiple relationships. If Alice and Bob from the previous
paragraph  had a child named Carol,  Alice would be both  Carol's mother and her
aunt.  Bob would be Carol's father and her uncle.  Eve would be Carol's maternal
and paternal grandparent.  Carol would be her own cousin.

Unknown people (those represented with `???` in the input file)  should never be
included in the output of any relationship queries.  A query for Alice's parents
should return the set containing only Eve.
