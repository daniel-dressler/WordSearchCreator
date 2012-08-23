class CreateWsGrids < ActiveRecord::Migration
  def change
    create_table :ws_grids do |t|
      t.string :grid
      t.references :set

      t.timestamps
    end
    add_index :ws_grids, :set_id
  end
end
