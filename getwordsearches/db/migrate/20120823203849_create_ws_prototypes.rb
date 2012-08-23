class CreateWsPrototypes < ActiveRecord::Migration
  def change
    create_table :ws_prototypes do |t|
      t.integer :height
      t.integer :width
      t.integer :seed
      t.references :set

      t.timestamps
    end
    add_index :ws_prototypes, :set_id
  end
end
