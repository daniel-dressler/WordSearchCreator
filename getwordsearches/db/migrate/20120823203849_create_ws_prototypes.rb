class CreateWsPrototypes < ActiveRecord::Migration
  def change
    create_table :ws_prototypes do |t|
      t.integer :height
      t.integer :width
      t.integer :seed
      t.references :word_search_set

      t.timestamps
    end
    add_index :ws_prototypes, :word_search_set_id
  end
end
