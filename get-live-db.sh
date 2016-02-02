drush @productivity.live sql-dump > now.sql --strict=0
cd www
drush sql-drop -y
drush sql-cli < ../now.sql
drush dis logs_http -y
drush cc all
echo done
