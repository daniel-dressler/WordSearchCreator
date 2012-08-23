class CreateWsAlphas < ActiveRecord::Migration
  def change
    create_table :ws_alphas do |t|
      t.string :chars
      t.references :set

      t.timestamps
    end
    add_index :ws_alphas, :set_id
  end
end
