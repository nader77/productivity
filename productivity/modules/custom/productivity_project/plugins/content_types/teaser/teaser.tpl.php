<div class="auction-summary">
<!--  In case auction finished -->
  <?php if (isset($auction_status_title)) : ?>
  <div>
    <h5><strong><?php print $auction_status_title ?></strong></h5>
    <label><?php print t('Sold for'); ?>:</label>
    <span><?php print $sold_for;?></span>
    <br>
    <label><?php print t('Opening price'); ?>:</label>
    <span><?php print $start_price;?></span>
  </div>
  <?php endif; ?>
  <!--  In case auction not finished -->
  <?php if (!isset($auction_status_title)) : ?>
    <label><?php print t('Sold for'); ?>:</label>
    <span><?php print $sold_for;?></span>
    <div><?php print $include_msg;?></div>
  <?php endif; ?>
</div>
