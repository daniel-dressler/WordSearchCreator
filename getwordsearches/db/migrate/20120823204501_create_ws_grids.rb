class CreateWsGrids < ActiveRecord::Migration
  def change
    create_table :ws_grids do |t|
      t.string :grid
      t.references :word_search_set

      t.timestamps
    end
    add_index :ws_grids, :word_search_set_id
  end
end
