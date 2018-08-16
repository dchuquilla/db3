CREATE OR REPLACE FUNCTION tg_kilometraje_semanal()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
  DECLARE delta_horas numeric;
  DECLARE delta_km numeric;
  DECLARE km_semanal numeric;
  DECLARE nuevo_update Timestamp Without Time Zone;
  DECLARE antiguo_update Timestamp Without Time Zone;
  DECLARE nuevo_km_actual numeric;
  DECLARE antiguo_km_actual numeric;
BEGIN
  nuevo_update = NEW.updated_at;
  antiguo_update = OLD.updated_at;
  nuevo_km_actual = NEW.current_km;
  antiguo_km_actual = OLD.current_km;
  SELECT EXTRACT(EPOCH FROM nuevo_update-antiguo_update)/3600 INTO delta_horas;
  delta_km = nuevo_km_actual - antiguo_km_actual;
  if (delta_horas > 0) && (NEW.current_km != OLD.current_km) then
    km_semanal = (delta_km/delta_horas)*168;
    update cars set week_km = km_semanal where id = OLD.id;
  end if;
  return NEW;
END
$function$

CREATE TRIGGER "procesarCambiosKmActual" AFTER UPDATE ON cars FOR EACH ROW EXECUTE PROCEDURE tg_kilometraje_semanal()

CREATE OR REPLACE FUNCTION tg_mantenimientos_basicos()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
  DECLARE i settings%rowtype;
  DECLARE contador integer;
  DECLARE edad integer;
  DECLARE km_estimado integer;
  DECLARE mes_estimado integer;
  DECLARE fecha_estimada Timestamp Without Time Zone;
  DECLARE tipo varchar(255);
BEGIN
  SELECT date_part('year', now()) - NEW.year INTO edad;
  FOR i IN SELECT * FROM settings WHERE car_age = edad AND car_type = NEW.car_type LOOP
    -- Obtener un numero aleatorio de un rango, meses y Km.
    SELECT floor(random() * (i.km_max-i.km_min+1) + i.km_min)::int INTO km_estimado;
    SELECT floor(random() * (i.month_max-i.month_min+1) + i.month_min)::int INTO mes_estimado;
    -- generar fecha furtura aproximanda de mantenimiento.
    SELECT now() + mes_estimado * interval '1 month' into fecha_estimada;
    INSERT INTO maintenance_histories ( car_id, maintenance_type, estimated_km, notified, scheduled_date, status, created_at, updated_at) VALUES ( NEW.id, i.maintenance_type, km_estimado, FALSE, fecha_estimada, 'Pendiente', now(), now());
  END LOOP;
  return NEW;
END
$function$

CREATE TRIGGER "crearMantenimientoBasicos" AFTER INSERT ON cars FOR EACH ROW EXECUTE PROCEDURE tg_mantenimientos_basicos();