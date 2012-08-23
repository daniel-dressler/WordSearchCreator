class CreateWsWordLists < ActiveRecord::Migration
  def change
    create_table :ws_word_lists do |t|
      t.string :words
      t.references :set

      t.timestamps
    end
    add_index :ws_word_lists, :set_id
  end
end
