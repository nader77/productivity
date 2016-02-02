drush @productivity.live sql-dump > now.sql --strict=0
cd www
drush sql-drop -y
drush sql-cli < ../now.sql
drush cc all
echo done
