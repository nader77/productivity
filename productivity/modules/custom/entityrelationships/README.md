This Drush command generates a graph of the entities, fields and their
relationship of a particular installation of Drupal.

# Usage

    $ drush entitygraph | dot -Gratio=0.7 -Eminlen=2 -T png -o ./test.png

Generates a graph in the PNG format.

# Caveats

* The command extracts the relationship information from the foreign key
  definition of entity types and fields.
