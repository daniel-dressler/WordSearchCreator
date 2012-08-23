class CreateWordSearchSets < ActiveRecord::Migration
  def change
    create_table :word_search_sets do |t|
      t.references :prototype
      t.references :goal
      t.references :swears
      t.references :words
      t.references :grids
      t.references :alphabet

      t.timestamps
    end
    add_index :word_search_sets, :prototype_id
    add_index :word_search_sets, :goal_id
    add_index :word_search_sets, :swears_id
    add_index :word_search_sets, :words_id
    add_index :word_search_sets, :grids_id
    add_index :word_search_sets, :alphabet_id
  end
end
